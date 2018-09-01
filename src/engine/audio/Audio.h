#pragma once

#include "Sound.h"
#include "Music.h"

class Audio {
public:
    virtual ~Audio();

    virtual void play_sound(const Sound& sound) = 0;

    virtual void play_music(const Music& music) = 0;
};
