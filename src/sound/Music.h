//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include <string>
#include <memory>

/* forward declarations begin */
typedef struct _Mix_Music Mix_Music;

/* forward declarations end */

class Music {
public:
    Music();

    explicit Music(char const* path);

    Music(Music const&) = delete;

    Music(Music&&) = delete;

    void load(char const* path);

    void play() const;

    struct FailedToLoadMusicException : std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    struct MixDeleter {
        void operator()(Mix_Music* p);
    };

    std::unique_ptr<Mix_Music, MixDeleter> mMusic;
};
