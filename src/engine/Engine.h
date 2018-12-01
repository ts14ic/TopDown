#pragma once

#include "graphic/Graphic.h"
#include "audio/Audio.h"
#include "input/Input.h"
#include "random/Random.h"
#include "clock/Clock.h"
#include <iosfwd>

class Engine {
public:
    virtual ~Engine() = 0;

    virtual void init(int screen_width, int screen_height) = 0;

    virtual void deinit() = 0;

    virtual Graphic& get_graphic() = 0;

    virtual Audio& get_audio() = 0;

    virtual Input& get_input() = 0;

    virtual Random& get_random() = 0;

    struct FailedEngineInitException : public std::runtime_error {
        explicit FailedEngineInitException(cstring message);
    };
};
