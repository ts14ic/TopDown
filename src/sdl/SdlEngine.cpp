#include "SdlEngine.h"
#include <SDL_image.h>
#include <SDL.h>

SdlEngine::FailedToLoadSoundException::FailedToLoadSoundException(const char* message)
        : runtime_error(message) {}

SdlEngine::FailedToLoadMusicException::FailedToLoadMusicException(const char* message)
        : runtime_error(message) {}

SdlEngine::SdlEngine(
        int screen_width,
        int screen_height
) : _graphic(screen_width, screen_height) {
}

SdlEngine::~SdlEngine() {
    _name_to_texture.clear();
    _name_to_music.clear();
    _name_to_sound.clear();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Texture& SdlEngine::get_texture(const std::string& name) {
    return _name_to_texture[name];
}

Music& SdlEngine::get_music(const std::string& name) {
    return _name_to_music[name];
}

Sound& SdlEngine::get_sound(const std::string& name) {
    return _name_to_sound[name];
}

void SdlEngine::load_texture(const std::string& name, const char* path) {
    _name_to_texture.insert(std::make_pair(name, load_texture(path)));
}

SdlTexture SdlEngine::load_texture(const char* path) {
    return _graphic.load_texture(path);
}

void SdlEngine::load_sound(const std::string& name, const char* path) {
    _name_to_sound.insert(std::make_pair(name, load_sound(path)));
}

void SdlEngine::load_music(const std::string& name, const char* path) {
    _name_to_music.insert(std::make_pair(name, load_music(path)));
}

SdlSound SdlEngine::load_sound(const char* path) {
    std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> new_sound{Mix_LoadWAV(path)};
    if (new_sound == nullptr) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }

    SdlSound sound{std::move(new_sound)};
    SDL_Log("SdlSound loaded: %s.\n", path);

    return sound;
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

InputContext& SdlEngine::get_input_context() {
    return _input;
}
