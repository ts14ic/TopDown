#pragma once

#include <stdexcept>
#include <iosfwd>

class Audio {
public:
    virtual ~Audio();

    struct FailedAudioInitException : public std::runtime_error {
        explicit FailedAudioInitException(const char* message);
    };

    virtual void load_sound(const std::string& name, const char* path) = 0;

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

    virtual void play_sound(const std::string& name) = 0;

    virtual void load_music(const std::string& name, const char* path) = 0;

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

    virtual void play_music(const std::string& name) = 0;
};
