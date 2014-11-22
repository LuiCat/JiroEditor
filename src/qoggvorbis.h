#ifndef _QOGGVORBIS_H_
#define _QOGGVORBIS_H_

#include <QObject>
#include <QString>
#include <QStringList>

#define DECLRARE_PROPERTY_WITH_GETTERS( aType, aProperty ) private:\
    aType m_ ## aProperty; public:\
    aType aProperty( void ) { return m_ ## aProperty; }

struct OggVorbis_File;// 前向声明

class QOggVorbis: public QObject
{
    Q_OBJECT
    Q_PROPERTY( quint16 audioFormat READ audioFormat )
    Q_PROPERTY( quint16 channels READ channels )
    Q_PROPERTY( quint32 sampleRate READ sampleRate )
    Q_PROPERTY( quint32 byteRate READ byteRate )
    Q_PROPERTY( quint16 blockAlign READ blockAlign )
    Q_PROPERTY( quint16 bitsPerSample READ bitsPerSample )
    Q_PROPERTY( QStringList userComments READ userComments )
    Q_PROPERTY( QString vendor READ vendor )
    Q_PROPERTY( qint8* data READ data )
    Q_PROPERTY( quint32 dataSize READ dataSize )
public:
    QOggVorbis( void );
    QOggVorbis( const QString& fileName );
    ~QOggVorbis( void );
    bool load( const QString& fileName );
    void clear( void );
private:
    bool getComment( OggVorbis_File* vf );
    bool decode( OggVorbis_File* vf );
    DECLRARE_PROPERTY_WITH_GETTERS( quint16, audioFormat )
    DECLRARE_PROPERTY_WITH_GETTERS( quint16, channels )
    DECLRARE_PROPERTY_WITH_GETTERS( quint32, sampleRate )       // 也就是频率Frequency
    DECLRARE_PROPERTY_WITH_GETTERS( quint32, byteRate )
    DECLRARE_PROPERTY_WITH_GETTERS( quint16, blockAlign )
    DECLRARE_PROPERTY_WITH_GETTERS( quint16, bitsPerSample )    // 也就是SampleRate
    DECLRARE_PROPERTY_WITH_GETTERS( QStringList, userComments )
    DECLRARE_PROPERTY_WITH_GETTERS( QString, vendor )
    DECLRARE_PROPERTY_WITH_GETTERS( qint8*, data )
    DECLRARE_PROPERTY_WITH_GETTERS( quint32, dataSize )
};

#endif // _QOGGVORBIS_H_
