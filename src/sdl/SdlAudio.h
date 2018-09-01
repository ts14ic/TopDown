#pragma once

#include <stdexcept>
#include "engine/audio/Audio.h"

class SdlAudio : public Audio {
public:
    SdlAudio();

    void play_sound(const Sound& sound) override;

    void play_music(const Music& music) override;

    struct FailedSdlMixerInitException : public std::runtime_error {
        explicit FailedSdlMixerInitException(const char* message);
    };
};
