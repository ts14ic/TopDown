//
// Created by ts14ic on 12/13/17.
//

#include "SdlAudioContext.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include <SDL_mixer.h>

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
