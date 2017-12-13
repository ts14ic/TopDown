//
// Created by ts14ic on 12/8/17.
//

#pragma once

#include <iosfwd>

class Texture;

class Sound;

class Music;

class GraphicContext;

class AudioContext;

class Assets {
public:
    virtual void setRenderContext(GraphicContext& graphicContext) = 0;

    virtual void setAudioContext(AudioContext& audioContext) = 0;

    virtual Texture& getTexture(std::string const& name) = 0;

    virtual void loadTexture(std::string const& name, const char* path) = 0;

    virtual Sound& getSound(std::string const& name) = 0;

    virtual void loadSound(std::string const& name, const char* path) = 0;

    virtual Music& music(std::string const& name) = 0;

    virtual ~Assets() = 0;
};
