#pragma once

#include <string>
#include <stdexcept>
#include <memory>

struct Mix_Chunk;

class Sound {
public:
    Sound();

    explicit Sound(char const* path);

    Sound(Sound const&) = delete;

    Sound(Sound&&) = delete;

    void load(char const* path);

    void play() const;

    struct FailedToLoadSoundException : public std::runtime_error {
        explicit FailedToLoadSoundException(const char* message);
    };

private:
    struct MixDeleter {
        void operator()(Mix_Chunk* p);
    };

    std::unique_ptr<Mix_Chunk, MixDeleter> mSound;
};
