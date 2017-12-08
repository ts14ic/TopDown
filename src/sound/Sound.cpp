#include "Sound.h"
#include <SDL_mixer.h>
#include <SDL_log.h>

Sound::Sound() = default;

Sound::Sound(char const* path) {
    load(path);
}

void Sound::load(char const* path) {
    mSound.reset(Mix_LoadWAV(path));
    if(!mSound) {
        throw FailedToLoadSoundException{Mix_GetError()};
    }
    SDL_Log("Sound loaded: %s.\n", path);
}

void Sound::play() const {
    if(mSound) {
        Mix_PlayChannel(-1, mSound.get(), 0);
    }
}

Sound::FailedToLoadSoundException::FailedToLoadSoundException(const char* message) : runtime_error(message) {}

void Sound::MixDeleter::operator()(Mix_Chunk* p) {
    Mix_FreeChunk(p);
}
