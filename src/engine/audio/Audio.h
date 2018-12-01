#pragma once

#include <utils/typedefs.h>
#include <stdexcept>
#include <iosfwd>

class Audio {
public:
    virtual ~Audio();

    struct FailedAudioInitException : public std::runtime_error {
        explicit FailedAudioInitException(cstring message);
    };

    virtual void load_sound(const std::string& name, cstring path) = 0;

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(cstring message);
    };

    virtual void play_sound(const std::string& name) = 0;

    virtual void load_music(const std::string& name, cstring path) = 0;

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(cstring message);
    };

    virtual void play_music(const std::string& name) = 0;
};
