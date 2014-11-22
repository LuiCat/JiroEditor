#ifndef _DS_MAIN
#define _DS_MAIN

#include <QString>
#include <QThread>

#define INITGUID
#include <dsound.h>

#include "notify.h"

class SoundBuffer
{

    LPDIRECTSOUNDBUFFER m_sound;
    WAVEFORMATEX format;    
    DSBUFFERDESC dsbdesc;

    LPDIRECTSOUNDNOTIFY lpNotify;

    double playbackSpeed;

    static double masterVolume;

public:

    SoundBuffer();
    ~SoundBuffer();

    void release();

    bool loadWav(const QString filename);
    bool loadOgg(const QString filename);

    bool isAvailable() const;

    void play();
    void play(DWORD st_pos);
    void stop();

    void setPos(DWORD npos);

    void setTime(double sec);
    double getTime() const;

    void setVolume(double volume);
    void setPan(long pan);

    Notify* setNotify(double sec);

};

#endif
