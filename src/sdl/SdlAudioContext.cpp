#include "SdlAudioContext.h"
#include "SdlSound.h"
#include "SdlMusic.h"

SdlAudioContext::SdlAudioContext() {
    if (0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSdlMixerInitException{Mix_GetError()};
    }
}

SdlAudioContext::FailedSdlMixerInitException::FailedSdlMixerInitException(const char *message)
        : runtime_error(message) {}

void SdlAudioContext::play_sound(const Sound &sound) {
    if (sound.is_loaded()) {
        Mix_PlayChannel(-1, dynamic_cast<const SdlSound &>(sound).get_wrapped_chunk(), 0);
    }
}

void SdlAudioContext::play_music(const Music &music) {
    if (music.is_loaded() && Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(dynamic_cast<const SdlMusic &>(music).get_wrapped_music(), -1);
    }
}
