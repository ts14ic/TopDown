//
// Created by ts14ic on 12/13/17.
//

#include "SdlAudioContext.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include <SDL_mixer.h>
#include <SDL_log.h>

SdlAudioContext::FailedToLoadSoundException::FailedToLoadSoundException(const char* message)
        : runtime_error(message) {}

SdlAudioContext::FailedToLoadMusicException::FailedToLoadMusicException(const char* message)
        : runtime_error(message) {}

SdlAudioContext::~SdlAudioContext() {
    Mix_Quit();
}

void SdlAudioContext::playSound(const Sound& sound) {
    if(sound.isLoaded()) {
        Mix_PlayChannel(-1, dynamic_cast<const SdlSound&>(sound).getWrappedChunk(), 0);
    }
}

void SdlAudioContext::playMusic(const Music& music) {
    if(music.isLoaded() && Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(dynamic_cast<const SdlMusic&>(music).getWrappedMusic(), -1);
    }
}

SdlSound SdlAudioContext::loadSound(const char* path) {
    std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> newSound{Mix_LoadWAV(path)};
    if(!newSound) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }

    SdlSound sound{std::move(newSound)};
    SDL_Log("SdlSound loaded: %s.\n", path);

    return sound;
}

SdlMusic SdlAudioContext::loadMusic(const char* path) {
    std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> newMusic{Mix_LoadMUS(path)};
    if(!newMusic) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SdlMusic music{std::move(newMusic)};
    SDL_Log("SdlMusic loaded: %s.\n", path);
    return music;
}
