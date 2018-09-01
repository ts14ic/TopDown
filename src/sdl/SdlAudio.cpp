#include <SDL_log.h>
#include "SdlAudio.h"
#include "SdlSound.h"
#include "SdlMusic.h"

SdlAudio::SdlAudio() {
    if (0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSdlMixerInitException{Mix_GetError()};
    }
}

SdlAudio::FailedSdlMixerInitException::FailedSdlMixerInitException(const char* message)
        : runtime_error(message) {}

SdlAudio::~SdlAudio() {
    _name_to_music.clear();
    _name_to_sound.clear();
    Mix_Quit();
}

void SdlAudio::play_sound(const Sound& sound) {
    if (sound.is_loaded()) {
        Mix_PlayChannel(-1, dynamic_cast<const SdlSound&>(sound).get_wrapped_chunk(), 0);
    }
}

Sound& SdlAudio::get_sound(const std::string& name) {
    return _name_to_sound[name];
}

void SdlAudio::load_sound(const std::string& name, const char* path) {
    _name_to_sound.insert(std::make_pair(name, load_sound(path)));
}

SdlSound SdlAudio::load_sound(const char* path) {
    std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> new_sound{Mix_LoadWAV(path)};
    if (new_sound == nullptr) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }

    SdlSound sound{std::move(new_sound)};
    SDL_Log("SdlSound loaded: %s.\n", path);

    return sound;
}

SdlAudio::FailedToLoadSoundException::FailedToLoadSoundException(const char* message)
        : runtime_error(message) {}

void SdlAudio::play_music(const Music& music) {
    if (music.is_loaded() && Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(dynamic_cast<const SdlMusic&>(music).get_wrapped_music(), -1);
    }
}

Music& SdlAudio::get_music(const std::string& name) {
    return _name_to_music[name];
}

void SdlAudio::load_music(const std::string& name, const char* path) {
    _name_to_music.insert(std::make_pair(name, load_music(path)));
}

SdlMusic SdlAudio::load_music(const char* path) {
    std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> new_music{Mix_LoadMUS(path)};
    if (new_music == nullptr) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SdlMusic music{std::move(new_music)};
    SDL_Log("SdlMusic loaded: %s.\n", path);
    return music;
}

SdlAudio::FailedToLoadMusicException::FailedToLoadMusicException(const char* message)
        : runtime_error(message) {}