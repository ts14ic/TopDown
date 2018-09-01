#pragma once

#include "Sound.h"
#include "Music.h"
#include <iosfwd>

class Audio {
public:
    virtual ~Audio();

    virtual void play_sound(const Sound& sound) = 0;

    virtual Sound& get_sound(const std::string& name) = 0;

    virtual void load_sound(const std::string& name, const char* path) = 0;

    virtual void play_music(const Music& music) = 0;
};
