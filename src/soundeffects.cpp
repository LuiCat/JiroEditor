#include "soundeffects.h"

#include <QDebug>

SoundEffects::SoundEffects()
    : dong_i(0)
    , ka_i(0)
    , balloon_i(0)
{
}

SoundEffects::~SoundEffects() {}

void SoundEffects::loadSounds()
{
    int i;
    for(i=0;i<1;++i)
    {
        dong[i].loadWav("data/dong.wav");
        ka[i].loadWav("data/ka.wav");
    }
    for(i=0;i<1;++i)
    {
        balloon[i].loadWav("data/balloon.wav");
    }
}

void SoundEffects::playSound(SoundType s)
{
    //static int count=0;
    //qDebug()<<"go!"<<count++;
    switch(s){
    case DONG:
        dong[dong_i].play(0);
        //dong_i=(dong_i+1)%32;
        break;
    case KA:
        ka[ka_i].play(0);
        //ka_i=(ka_i+1)%32;
        break;
    case BALLOON:
        balloon[balloon_i].play(0);
        //balloon_i=(balloon_i+1)%5;
        break;
    }
}
