#ifndef SOUNDCORE_H
#define SOUNDCORE_H

#include <QObject>
#include <QWindow>
#include <dsound.h>

class SoundCore : public QObject
{
    static SoundCore *instance;

    LPDIRECTSOUND8 lpDirectSound;

    HWND hWnd;

public:
    explicit SoundCore(QObject *parent, HWND winId);
    ~SoundCore();

    bool initialize();
    void release();

    static SoundCore& getInstance();
    static LPDIRECTSOUND8 getDirectSound();

};

#endif // SOUNDCORE_H
