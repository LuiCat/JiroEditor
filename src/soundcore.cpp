#include "soundcore.h"

#include <QDebug>

SoundCore *SoundCore::instance=NULL;

SoundCore::SoundCore(QObject *parent, HWND winId) :
    QObject(parent),
    lpDirectSound(NULL)
{
    instance=this;
    hWnd=winId;
    if(!initialize())
        qDebug()<<"Dsound initialize failed";
}

SoundCore::~SoundCore()
{
    release();
}

bool SoundCore::initialize()
{
    DirectSoundCreate8(NULL, &lpDirectSound, NULL);
    if(FAILED(lpDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))  //DSSCL_EXCLUSIVE
        return false;
    return true;
}

void SoundCore::release()
{
    if(lpDirectSound)
        lpDirectSound->Release();
    lpDirectSound=NULL;
}

SoundCore& SoundCore::getInstance()
{
    return *instance;
}

LPDIRECTSOUND8 SoundCore::getDirectSound()
{
    return instance->lpDirectSound;
}
