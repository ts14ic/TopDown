#pragma once

#include "audio/SdlAudio.h"
#include "engine_sdl/clock/SdlClockEngine.h"
#include "graphic/SdlGraphic.h"
#include "input/SdlInput.h"
#include <engine_std/Mt19937Random.h>
#include <engine/Engine.h>
#include <unordered_map>
#include <engine_sdl/log/SdlLogger.h>

class SdlEngine : public Engine {
public:
    SdlEngine();

    ~SdlEngine() override;

    void init(int screen_width, int screen_height) override;

    void deinit() override;

    Graphic& get_graphic() override;

    Audio& get_audio() override;

    Input& get_input() override;

    Random& get_random() override;

private:
    Mt19937Random _random;

    SdlLogger _logger;
    SdlGraphic _graphic;
    SdlAudio _audio;
    SdlInput _input;
};
