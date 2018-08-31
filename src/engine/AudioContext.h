#pragma once

#include "resources/Sound.h"
#include "resources/Music.h"

class AudioContext {
public:
    virtual ~AudioContext();

    virtual void playSound(const Sound& sound) = 0;

    virtual void playMusic(const Music& music) = 0;
};
