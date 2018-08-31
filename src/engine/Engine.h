#pragma once

#include "engine/graphic/Texture.h"
#include "engine/audio/Sound.h"
#include "engine/audio/Music.h"
#include "engine/clock/Clock.h"
#include <iosfwd>

class Engine {
public:
    virtual Texture& get_texture(const std::string &name) = 0;

    virtual Sound& get_sound(const std::string &name) = 0;

    virtual Music& get_music(const std::string &name) = 0;

    virtual const Clock& get_clock() = 0;

    virtual void load_texture(const std::string &name, const char *path) = 0;

    virtual void load_sound(const std::string &name, const char *path) = 0;

    virtual void load_music(const std::string &name, const char *path) = 0;

    virtual ~Engine() = 0;
};
