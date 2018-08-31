#pragma once

#include "engine/audio/AudioContext.h"

class SdlAudioContext : public AudioContext {
public:
    void play_sound(const Sound &sound) override;

    void play_music(const Music &music) override;
};
