#pragma once

#include "engine/Engine.h"
#include "audio/SdlAudio.h"
#include "clock/SdlClock.h"
#include "graphic/SdlGraphic.h"
#include "SdlGuard.h"
#include "engine_sdl/input/SdlInput.h"
#include "random/Mt19937Random.h"
#include <unordered_map>

class SdlEngine : public Engine {
public:
    SdlEngine(int screen_width, int screen_height);

    Graphic& get_graphic() override;

    Audio& get_audio() override;

    Input& get_input() override;

    Random& get_random() override;

    const Clock& get_clock() override;

    struct FailedSdlInitException : public std::runtime_error {
        explicit FailedSdlInitException(const char* message);
    };
private:
    Mt19937Random _random;

    SdlGuard _sdl_guard; /* Must be higher than all other sdl systems */
    SdlGraphic _graphic;
    SdlAudio _audio;
    SdlInput _input;
    SdlClock _clock;
};
