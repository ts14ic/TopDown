//
// Created by ts14ic on 12/13/17.
//

#include "SdlAudioContext.h"
#include "SdlSound.h"
#include <SDL_mixer.h>
#include <SDL_log.h>

SdlAudioContext::FailedToLoadSoundException::FailedToLoadSoundException(const char* message)
        : runtime_error(message) {}

void SdlAudioContext::playSound(const Sound& sound) {
    if(sound.isLoaded()) {
        Mix_PlayChannel(-1, dynamic_cast<const SdlSound&>(sound).getWrappedChunk(), 0);
    }
}

void SdlAudioContext::playMusic(const Music& music) {
    // todo stub
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

SdlAudioContext::~SdlAudioContext() {
    Mix_Quit();
}
