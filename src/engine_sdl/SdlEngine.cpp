#include "SdlEngine.h"
#include <SDL_image.h>
#include <SDL.h>
#include <engine/log/Log.h>

SdlEngine::SdlEngine(
        int screen_width,
        int screen_height
) : _sdl_guard{}, _graphic(screen_width, screen_height) {
    Log::install_logger(_sdl_logger);
}

SdlEngine::~SdlEngine() {
    Log::uninstall_logger(_sdl_logger);
}

const Clock& SdlEngine::get_clock() {
    return _clock;
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
