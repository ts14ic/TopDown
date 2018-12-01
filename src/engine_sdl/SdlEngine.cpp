#include "SdlEngine.h"
#include <SDL_image.h>
#include <SDL.h>
#include <engine/log/Log.h>

SdlEngine::SdlEngine() = default;

SdlEngine::~SdlEngine() = default;

void SdlEngine::init(int screen_width, int screen_height) {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if (SDL_Init(initFlags) != 0) {
        throw Engine::FailedEngineInitException{SDL_GetError()};
    }

    Clock::install_clock_engine(std::make_unique<SdlClockEngine>());

    _logger.init();
    Log::install_logger(_logger);

    _audio.init();
    _graphic.init(screen_width, screen_height);
}

void SdlEngine::deinit() {
    _graphic.deinit();
    _audio.deinit();

    Log::uninstall_logger(_logger);

    Clock::uninstall_clock_engine();

    SDL_Quit();
}

Graphic& SdlEngine::get_graphic() {
    return _graphic;
}

Audio& SdlEngine::get_audio() {
    return _audio;
}

Random& SdlEngine::get_random() {
    return _random;
}

Input& SdlEngine::get_input() {
    return _input;
}
