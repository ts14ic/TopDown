#pragma once

#include "engine/Engine.h"
#include "random/Mt19937Random.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include "SdlClock.h"
#include "SdlGuard.h"
#include "SdlGraphic.h"
#include "SdlAudio.h"
#include "SdlInput.h"
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
