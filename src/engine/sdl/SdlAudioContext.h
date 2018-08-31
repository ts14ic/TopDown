#pragma once

#include "engine/AudioContext.h"

class SdlAudioContext : public AudioContext {
public:
    void playSound(const Sound& sound) override;

    void playMusic(const Music& music) override;
};
