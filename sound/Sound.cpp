#include "Sound.h"
#include <SDL_mixer.h>
#include <SDL_log.h>
#include <unordered_map>

Sound::Sound() {}

Sound::Sound(char const* path) {
    load(path);
}

Sound::~Sound() {
    if(_chunk) {
        Mix_FreeChunk(_chunk);
    }
}

void Sound::load(char const* path) {
    _chunk = Mix_LoadWAV(path);
    if(!_chunk) {
        SDL_Log("Failed loading %s. %s.\n", path, Mix_GetError());
        throw FailedToLoadSoundException{};
    }
    SDL_Log("Loaded sound: %s.\n", path);
}

void Sound::play() const {
    if(_chunk) {
        Mix_PlayChannel(-1, _chunk, 0);
    }
}

Sound& sounds(std::string const& name) {
    static std::unordered_map<std::string, Sound> ret;
    return ret[name];
}
