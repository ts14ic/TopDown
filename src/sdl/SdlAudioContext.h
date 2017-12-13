//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/AudioContext.h"
#include <stdexcept>

class SdlSound;

class SdlMusic;

class SdlAudioContext : public AudioContext {
public:
    ~SdlAudioContext() override;

    void playSound(const Sound& sound) override;

    void playMusic(const Music& music) override;

    SdlSound loadSound(const char* path);

    SdlMusic loadMusic(const char* path);

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };
};
