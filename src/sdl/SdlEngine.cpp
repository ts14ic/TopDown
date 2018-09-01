#include "SdlEngine.h"
#include <SDL_image.h>
#include <SDL.h>

SdlEngine::FailedToLoadMusicException::FailedToLoadMusicException(const char* message)
        : runtime_error(message) {}

SdlEngine::SdlEngine(
        int screen_width,
        int screen_height
) : _graphic(screen_width, screen_height) {
}

SdlEngine::~SdlEngine() {
    _name_to_music.clear();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Music& SdlEngine::get_music(const std::string& name) {
    return _name_to_music[name];
}

void SdlEngine::load_music(const std::string& name, const char* path) {
    _name_to_music.insert(std::make_pair(name, load_music(path)));
}

SdlMusic SdlEngine::load_music(const char* path) {
    std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> new_music{Mix_LoadMUS(path)};
    if (new_music == nullptr) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SdlMusic music{std::move(new_music)};
    SDL_Log("SdlMusic loaded: %s.\n", path);
    return music;
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
