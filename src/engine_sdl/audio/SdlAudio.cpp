#include "SdlAudio.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include <SDL_log.h>

SdlAudio::SdlAudio() = default;

SdlAudio::~SdlAudio() = default;

void SdlAudio::init() {
    if (0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedAudioInitException{Mix_GetError()};
    }
}

void SdlAudio::deinit() {
    _name_to_music.clear();
    _name_to_sound.clear();
    Mix_Quit();
}

void SdlAudio::play_sound(const SdlSound& sound) {
    if (sound.is_loaded()) {
        Mix_PlayChannel(-1, sound.get_wrapped_chunk(), 0);
    }
}

void SdlAudio::play_sound(const std::string& name) {
    play_sound(_name_to_sound[name]);
}

void SdlAudio::load_sound(const std::string& name, cstring path) {
    _name_to_sound.insert(std::make_pair(name, load_sound(path)));
}

SdlSound SdlAudio::load_sound(cstring path) {
    ChunkHandle chunk_handle{Mix_LoadWAV(path)};
    if (chunk_handle == nullptr) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }

    SdlSound sound{std::move(chunk_handle)};
    SDL_Log("SdlSound loaded: %s.\n", path);
    return sound;
}

void SdlAudio::play_music(const std::string& name) {
    play_music(_name_to_music[name]);
}

void SdlAudio::play_music(const SdlMusic& music) {
    if (music.is_loaded() && Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(music.get_wrapped_music(), -1);
    }
}

void SdlAudio::load_music(const std::string& name, cstring path) {
    _name_to_music.insert(std::make_pair(name, load_music(path)));
}

SdlMusic SdlAudio::load_music(cstring path) {
    MusicHandle music_handle{Mix_LoadMUS(path)};
    if (music_handle == nullptr) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SdlMusic music{std::move(music_handle)};
    SDL_Log("SdlMusic loaded: %s.\n", path);
    return music;
}