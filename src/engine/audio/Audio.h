#pragma once

#include <iosfwd>

class Audio {
public:
    virtual ~Audio();

    virtual void load_sound(const std::string& name, const char* path) = 0;

    virtual void play_sound(const std::string& name) = 0;

    virtual void load_music(const std::string& name, const char* path) = 0;

    virtual void play_music(const std::string& name) = 0;
};
