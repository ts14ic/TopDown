#pragma once

#include <string>

struct FailedToLoadSoundException {
};

/* forward declarations begin */
struct Mix_Chunk;

/* forward declarations end */

class Sound {
public:
    Sound();

    explicit Sound(char const* path);

    ~Sound();

    Sound(Sound const&) = delete;

    Sound(Sound&&) = delete;

    void load(char const* path);

    void play() const;

private:
    Mix_Chunk* _chunk = nullptr;
};

Sound& sounds(std::string const& name);
