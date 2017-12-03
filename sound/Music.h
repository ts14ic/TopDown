//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include <string>

/* forward declarations begin */
struct _Mix_Music;

/* forward declarations end */

class Music {
public:
    Music();

    explicit Music(char const* path);

    ~Music();

    Music(Music const&) = delete;

    Music(Music&&) = delete;

    void load(char const* path);

    void play() const;

    struct FailedToLoadMusicException : std::runtime_error {
        explicit FailedToLoadMusicException(const char* message);
    };

private:
    _Mix_Music* _mus;
};

Music& music(std::string const& name);
