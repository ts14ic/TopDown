//
// Created by ts14ic on 12/8/17.
//

#pragma once

#include "Texture.h"
#include "Sound.h"
#include "Music.h"
#include "../Clock.h"
#include <iosfwd>

class Resources {
public:
    virtual Texture& getTexture(const std::string& name) = 0;

    virtual Sound& getSound(const std::string& name) = 0;

    virtual Music& getMusic(const std::string& name) = 0;

    virtual const Clock& getClock() = 0;

    virtual void loadTexture(const std::string& name, const char* path) = 0;

    virtual void loadSound(const std::string& name, const char* path) = 0;

    virtual void loadMusic(const std::string& name, const char* path) = 0;

    virtual ~Resources() = 0;
};
