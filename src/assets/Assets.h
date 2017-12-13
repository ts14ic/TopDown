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

    virtual Texture& getTexture(const std::string& name) = 0;

    virtual void loadTexture(const std::string& name, const char* path) = 0;

    virtual Sound& getSound(const std::string& name) = 0;

    virtual void loadSound(const std::string& name, const char* path) = 0;

    virtual Music& getMusic(const std::string& name) = 0;

    virtual void loadMusic(const std::string& name, const char* path) = 0;

    virtual ~Assets() = 0;
};
