#pragma once

#include "engine/graphic/Graphic.h"
#include "engine/audio/Audio.h"
#include "engine/input/Input.h"
#include "engine/random/Random.h"
#include "engine/clock/Clock.h"
#include <iosfwd>

class Engine {
public:
    virtual ~Engine() = 0;

    virtual Graphic& get_graphic() = 0;

    virtual Audio& get_audio() = 0;

    virtual Input& get_input() = 0;

    virtual Random& get_random() = 0;

    virtual const Clock& get_clock() = 0;

    struct FailedEngineInitException : public std::runtime_error {
        explicit FailedEngineInitException(const char* message);
    };
};
