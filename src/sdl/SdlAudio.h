#pragma once

#include "engine/audio/Audio.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include <stdexcept>
#include <unordered_map>

class SdlAudio : public Audio {
public:
    SdlAudio();

    ~SdlAudio() override;

    void play_sound(const std::string& name) override;

    void load_sound(const std::string& name, const char* path) override;

    void play_music(const std::string& name) override;

    void load_music(const std::string& name, const char* path) override;

    struct FailedSdlMixerInitException : public std::runtime_error {
        explicit FailedSdlMixerInitException(const char* message);
    };

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    SdlSound load_sound(const char* path);

    void play_sound(const Sound& sound);

    SdlMusic load_music(const char* path);

    void play_music(const Music& music);

    std::unordered_map<std::string, SdlSound> _name_to_sound;
    std::unordered_map<std::string, SdlMusic> _name_to_music;
};
