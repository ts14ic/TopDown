//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include <string>
#include <memory>

typedef struct _Mix_Music Mix_Music;

class Music {
public:
    Music();

    explicit Music(char const* path);

    Music(Music const&) = delete;

    Music(Music&&) = delete;

    void load(char const* path);

    void play() const;

    struct FailedToLoadMusicException : public std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    struct MixDeleter {
        void operator()(Mix_Music* p);
    };

    std::unique_ptr<Mix_Music, MixDeleter> mMusic;
};
