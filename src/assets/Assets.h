//
// Created by ts14ic on 12/8/17.
//

#pragma once

#include <iosfwd>

class Texture;

class Sound;

class Music;

class Assets {
public:
    virtual Texture& texture(std::string const& name) = 0;

    virtual Music& music(std::string const& name) = 0;

    virtual Sound& sound(std::string const& name) = 0;

    virtual ~Assets() = 0;
};
