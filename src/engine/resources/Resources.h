#pragma once

#include "Texture.h"
#include "Sound.h"
#include "Music.h"
#include "engine/Clock.h"
#include <iosfwd>

class Resources {
public:
    virtual Texture& get_texture(const std::string &name) = 0;

    virtual Sound& get_sound(const std::string &name) = 0;

    virtual Music& get_music(const std::string &name) = 0;

    virtual const Clock& get_clock() = 0;

    virtual void load_texture(const std::string &name, const char *path) = 0;

    virtual void load_sound(const std::string &name, const char *path) = 0;

    virtual void load_music(const std::string &name, const char *path) = 0;

    virtual ~Resources() = 0;
};
