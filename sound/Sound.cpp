#include "Sound.h"
#include <SDL_mixer.h>
#include <SDL_log.h>
#include <unordered_map>

Sound::Sound() {}

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

Sound& sounds(std::string const& name) {
    static std::unordered_map<std::string, Sound> ret;
    return ret[name];
}

Sound::FailedToLoadSoundException::FailedToLoadSoundException(const char* message) : runtime_error(message) {}

void Sound::MixDeleter::operator()(Mix_Chunk* p) {
    Mix_FreeChunk(p);
}
