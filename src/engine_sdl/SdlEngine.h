#pragma once

#include "SdlGuard.h"
#include "audio/SdlAudio.h"
#include "clock/SdlClock.h"
#include "graphic/SdlGraphic.h"
#include "input/SdlInput.h"
#include <engine_std/Mt19937Random.h>
#include <engine/Engine.h>
#include <unordered_map>
#include <engine_sdl/log/SdlLogger.h>

class SdlEngine : public Engine {
public:
    SdlEngine(int screen_width, int screen_height);

    Graphic& get_graphic() override;

    Audio& get_audio() override;

    Input& get_input() override;

    Random& get_random() override;

    const Clock& get_clock() override;

    ~SdlEngine() override;

private:
    Mt19937Random _random;

    SdlGuard _sdl_guard; /* Must be higher than all other sdl systems */
    SdlLogger _sdl_logger;
    SdlGraphic _graphic;
    SdlAudio _audio;
    SdlInput _input;
    SdlClock _clock;
};
