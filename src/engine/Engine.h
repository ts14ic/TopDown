#pragma once

#include "engine/graphic/Texture.h"
#include "engine/random/Random.h"
#include "engine/audio/Sound.h"
#include "engine/audio/AudioContext.h"
#include "engine/input/InputContext.h"
#include "engine/audio/Music.h"
#include "engine/clock/Clock.h"
#include <iosfwd>

class Engine {
public:
    virtual GraphicContext& get_graphic_context() = 0;

    virtual AudioContext& get_audio_context() = 0;

    virtual InputContext& get_input_context() = 0;

    virtual Random& get_random() = 0;

    virtual const Clock& get_clock() = 0;

    virtual Texture& get_texture(const std::string& name) = 0;

    virtual void load_texture(const std::string& name, const char* path) = 0;

    virtual Sound& get_sound(const std::string& name) = 0;

    virtual void load_sound(const std::string& name, const char* path) = 0;

    virtual Music& get_music(const std::string& name) = 0;

    virtual void load_music(const std::string& name, const char* path) = 0;

    virtual ~Engine() = 0;
};
