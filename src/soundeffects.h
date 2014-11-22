#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include "soundbuffer.h"

enum SoundType{
    DONG=1, KA=2, BALLOON=7
};

class SoundEffects
{
    SoundBuffer dong[32];
    SoundBuffer ka[32];
    SoundBuffer balloon[5];

    int dong_i,ka_i,balloon_i;

public:

    SoundEffects();
    ~SoundEffects();

    void loadSounds();

    void playSound(enum SoundType s);

};

#endif // SOUNDEFFECTS_H
