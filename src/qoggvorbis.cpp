
/*
 * 源代码来自： http://blog.csdn.net/jiangcaiyang123
 */

#include <QDebug>
#include <QFile>
#include <QMutex>
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
#include "qoggvorbis.h"

/*---------------------------------------------------------------------------*/
QOggVorbis::QOggVorbis( void )
{
    m_data = 0;
    clear( );
}
/*---------------------------------------------------------------------------*/
QOggVorbis::QOggVorbis( const QString& fileName )
{
    m_data = 0;
    load( fileName );
}

/*---------------------------------------------------------------------------*/
QOggVorbis::~QOggVorbis( void )
{
    if ( m_data ) delete m_data;
}
/*---------------------------------------------------------------------------*/
// 全局变量（要进行线程保护）
ogg_int64_t				g_Pos			= 0;
ogg_int64_t				g_Size			= 0;
/*---------------------------------------------------------------------------*/
// 这些是为了载入Ogg资源而自定义的类文件I/O操作函数
size_t OggRsrc_Read( void* buffer, size_t elementSize, size_t count, void* dataStream )
{
    if ( g_Size - g_Pos < elementSize * count )			// 只剩下一点没有读完了不够一块2048字节
    {
        memcpy( buffer, (qint8*)dataStream + g_Pos, (size_t)( g_Size - g_Pos ) );
        g_Pos = g_Size;
        return (size_t)( g_Size - g_Pos );// 返回读取的个数
    }
    else
    {
        memcpy( buffer, (qint8*)dataStream + g_Pos, elementSize * count );
        g_Pos += count * elementSize;
    }
    return count;// 返回读取的个数
}

int OggRsrc_Seek( void* src, ogg_int64_t offset, int whence )// 寻找字节的函数
{
    if ( src == NULL ) return -1;

    switch( whence )
    {
    case SEEK_SET:// 从头开始
        if ( offset >= 0 ) g_Pos = offset * sizeof( qint8 );
        break;
    case SEEK_CUR:// 从游标出开始
        g_Pos += offset * sizeof( qint8 ); break;
    case SEEK_END:// 从末尾开始
        if ( offset <= 0 ) g_Pos = g_Size + ( offset + 1 ) * sizeof( qint8 );
        else return -1;
    }

    return 0;
}

size_t OggRsrc_Close( void* )
{
    return 0;// 因为已经从内存中读取，所以什么也不做，直接返回
}

long OggRsrc_Tell( void* )// 获取字节数
{
    return (long)g_Pos;
}
/*---------------------------------------------------------------------------*/
bool QOggVorbis::load( const QString& fileName )
{
    clear( );       // 清除原先拥有的数据

    QFile file( fileName );
    if ( !file.open( QIODevice::ReadOnly ) )                // 打开文件
    {
        qDebug( ) << tr( "QOggVorbis::Load: Cannot open vorbis file or resource." );
        return false;
    }
    QByteArray vorbisData( file.readAll( ) );               // 文件内容读至ByteArray中
    char* pData = vorbisData.data( );
    file.close( );

    OggVorbis_File vf;

    g_Pos = 0, g_Size = 0;// 清零
    g_Size = vorbisData.size( );

    ov_callbacks rsrcCallBack =
    {
        (size_t (*)(void *, size_t, size_t, void *))	OggRsrc_Read,
        (int (*)(void *, ogg_int64_t, int))				OggRsrc_Seek,
        (int (*)(void *))								OggRsrc_Close,
        (long (*)(void *))								OggRsrc_Tell
    };

    if ( ov_open_callbacks( pData, &vf, NULL, 0, rsrcCallBack ) < 0 )
    {
        qDebug( ) << tr( "QOggVorbis::Load: Read OggVorbis file error." );
        return false;
    }

    bool ret = true;
    ret &= getComment( &vf );
    ret &= decode( &vf );
    return ret;
}
/*---------------------------------------------------------------------------*/
bool QOggVorbis::getComment( OggVorbis_File* vf )			// 获得额外信息
{
    vorbis_comment* pComments = ov_comment( vf, -1 );
    for ( int i = 0; i < pComments->comments; ++i )
    {
        m_userComments.append( pComments->user_comments[i] );
    }
    m_vendor = pComments->vendor;
    return true;
}
/*---------------------------------------------------------------------------*/
#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM     1
#endif
bool QOggVorbis::decode( OggVorbis_File* vf )
{    
    ogg_int64_t pos = 4;
    char pcmOut[4096];												// 预留四千字节给Vorbis缓存
    int eof = 0;
    int current_section = 0;

    int samples						= (int)ov_pcm_total( vf, -1 );					// 采样
    int channels					= ov_info( vf, -1 )->channels;					// 通道数
    quint32 sampleRate		        = ov_info( vf, -1 )->rate;						// 采样率
    uint max_size                   = channels * 2 * samples + 4;

    bool flag_readStop=false;

    if ( samples > 0 )
    {
        m_data = new qint8[ max_size ];
    }

    // 读取数据

    while (!flag_readStop && !eof)
    {
        long ret = ov_read(vf, pcmOut, sizeof( pcmOut ), 0, 2, 1, &current_section);

        if (ret == 0 )
        {
            eof = 1;
        }
        else if (ret < 0)
        {
            if (ret == OV_EBADLINK)
            {
                qDebug( ) << tr( "QOggVorbis::Decode: Internal error, bitstream corrupted." );
                ov_clear( vf );		// 文件内部错误，清除缓冲区（原因：比特流崩溃）
                return false;       // 退出
            }
        }
        else
        {
            int t;
            for ( t = 0; t < ret; t++ )// 将缓冲区的数据填入向量中
            {
                if(pos==max_size)
                {
                    flag_readStop=true;
                    break;
                }
                m_data[ pos++ ] = pcmOut[t];
            }
        }
    }

    // 数据读取成功，清除缓冲区

    ov_clear( vf );

    // 设置波形文件信息

    m_audioFormat						= WAVE_FORMAT_PCM;
    m_bitsPerSample						= 16;
    m_blockAlign						= quint16( 2 * channels );
    m_byteRate							= sampleRate * channels * 2;
    m_channels      					= quint16( channels );
    m_sampleRate						= sampleRate;
    m_dataSize						    = (quint32)( channels * 2 * samples );
    return true;
}
#undef WAVE_FORMAT_PCM
/*---------------------------------------------------------------------------*/
void QOggVorbis::clear( void )
{
    m_audioFormat     = 0;
    m_channels        = 0;
    m_sampleRate      = 0;
    m_byteRate        = 0;
    m_blockAlign      = 0;
    m_bitsPerSample   = 0;
    m_userComments.clear( );
    m_vendor.clear( );
    m_dataSize        = 0;
    if ( m_data ) { delete m_data; m_data = 0; }
}
