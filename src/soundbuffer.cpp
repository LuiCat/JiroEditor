#include "soundbuffer.h"
#include "soundcore.h"

#include "qoggvorbis.h"

#include <QDebug>
#include <QFile>

#include <cmath>

double SoundBuffer::masterVolume=0.5;

SoundBuffer::SoundBuffer() :
    m_sound(0),
    lpNotify(0),
    playbackSpeed(1.0)
{

}

SoundBuffer::~SoundBuffer()
{
    release();
}

void SoundBuffer::release()
{
    if(m_sound!=0)
    {
        m_sound->Release();
        m_sound=0;
    }

    if(lpNotify!=0)
    {
        lpNotify->Release();
        lpNotify=0;
    }

}

bool SoundBuffer::loadWav(const QString filename)
{
    release();

    QFile audio_file(filename);
    QByteArray audio_data;

    memset(&format, 0, sizeof(WAVEFORMATEX));

    if(!audio_file.open(QIODevice::ReadOnly))
        return false;

    DWORD formatSize;
    DWORD dataSize;

    audio_file.seek(20);
    audio_file.read((char *)&format, sizeof(PCMWAVEFORMAT));
    audio_file.seek(16);
    audio_file.read((char*)&formatSize, 4);
    audio_file.seek(24+formatSize);
    audio_file.read((char*)&dataSize, 4);
    audio_file.seek(28+formatSize);
    audio_data=audio_file.read(dataSize);
    audio_file.close();

    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;// | DSBCAPS_CTRLFREQUENCY;
    dsbdesc.dwBufferBytes = audio_data.size();
    dsbdesc.lpwfxFormat = &format;

    if(FAILED(SoundCore::getDirectSound()->CreateSoundBuffer(&dsbdesc, &m_sound, NULL)))
        return false;

    LPVOID lpvWrite;
    DWORD  dwLength;

    if (m_sound->Lock(0, 0, &lpvWrite, &dwLength, NULL, 0, DSBLOCK_ENTIREBUFFER)==S_OK)
    {
        memcpy(lpvWrite, audio_data.constData(), dwLength);
        m_sound->Unlock(lpvWrite, dwLength, NULL, 0);
    }

    setVolume(1.0);

    return true;
}

bool SoundBuffer::loadOgg(const QString filename)
{
    release();

    QOggVorbis m_OggVorbis;

    if (!m_OggVorbis.load(filename))return false;

    format.wFormatTag = 1;
    format.nSamplesPerSec = m_OggVorbis.sampleRate();
    format.nChannels = m_OggVorbis.channels();
    format.wBitsPerSample = m_OggVorbis.bitsPerSample();
    format.nBlockAlign = format.wBitsPerSample*format.nChannels/8;
    format.nAvgBytesPerSec = format.nSamplesPerSec*format.nBlockAlign;
    format.cbSize = 0;

    qDebug() << "Ogg file information: " <<
                "[sampleRate: " << format.nSamplesPerSec <<
                "][channels: " << format.nChannels <<
                "][sampleSize: " << format.wBitsPerSample <<
                ']';

    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPOSITIONNOTIFY;
    dsbdesc.dwBufferBytes = m_OggVorbis.dataSize();
    dsbdesc.lpwfxFormat = &format;

    if(FAILED(SoundCore::getDirectSound()->CreateSoundBuffer(&dsbdesc, &m_sound, NULL)))
        return false;

    LPVOID lpvWrite;
    DWORD  dwLength;

    if (m_sound->Lock(0, 0, &lpvWrite, &dwLength, NULL, 0, DSBLOCK_ENTIREBUFFER)==S_OK)
    {
        memcpy(lpvWrite, m_OggVorbis.data(), dwLength);
        m_sound->Unlock(lpvWrite, dwLength, NULL, 0);
    }

    setVolume(1.0);

    return true;
}

bool SoundBuffer::isAvailable() const
{
    return m_sound!=0;
}

void SoundBuffer::play(DWORD st_pos){
    if(m_sound==0)return;
    m_sound->SetCurrentPosition(st_pos);
    m_sound->Play(0,0,0);
}

void SoundBuffer::play(){
    if(m_sound==0)return;
    m_sound->Play(0,0,0);
}

void SoundBuffer::stop(){
    if(m_sound==0)return;
    m_sound->Stop();
}

void SoundBuffer::setPos(DWORD npos){
    if(m_sound==0)return;
    m_sound->SetCurrentPosition(npos);
}

void SoundBuffer::setTime(double sec)
{
    if(m_sound==0)return;
    if(sec<0.0)sec=0.0;
    DWORD tfrq=format.nAvgBytesPerSec;
    m_sound->SetCurrentPosition(sec*tfrq);
}

double SoundBuffer::getTime() const{
    if(m_sound==0)return 0.0;
    DWORD tpos, tfrq=format.nAvgBytesPerSec;
    m_sound->GetCurrentPosition(&tpos,0);
    return (double)tpos/tfrq;
}

void SoundBuffer::setVolume(double volume){
    if(m_sound==0)return;
    m_sound->SetVolume(2000.0 * log10(volume*masterVolume));
}

void SoundBuffer::setPan(long pan){
    if(m_sound==0)return;
    m_sound->SetPan(pan);
}

Notify* SoundBuffer::setNotify(double sec)
{
    if(!m_sound)
        return 0;

    if(!lpNotify)
    {
        if(m_sound->QueryInterface(IID_IDirectSoundNotify8, (LPVOID*)&lpNotify)!=S_OK)
        {
            return 0;
        }
    }

    Notify *notify=new Notify();
    notify->multipleNotify();

    DSBPOSITIONNOTIFY PositionNotify;

    PositionNotify.dwOffset=(sec>0.0?format.nAvgBytesPerSec*sec:dsbdesc.dwBufferBytes-1);
    PositionNotify.hEventNotify=notify->getEventHandle();

    lpNotify->SetNotificationPositions(1, &PositionNotify);

    return notify;
}

