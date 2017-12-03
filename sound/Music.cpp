//
// Created by ts14ic on 12/3/17.
//

#include <SDL_mixer.h>
#include <SDL_log.h>
#include <unordered_map>
#include "Music.h"

Music::Music()
        : _mus{nullptr} {}

Music::~Music() {
    if(_mus) {
        Mix_FreeMusic(_mus);
    }
}

Music::Music(char const* path) {
    load(path);
}

void Music::load(char const* path) {
    _mus = Mix_LoadMUS(path);
    if(!_mus) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SDL_Log("Loaded music: %s.\n", path);
}

void Music::play() const {
    if(_mus && Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(_mus, -1);
    }
}

Music& music(std::string const& name) {
    static std::unordered_map<std::string, Music> ret;
    return ret[name];
}

Music::FailedToLoadMusicException::FailedToLoadMusicException(const char* message) : runtime_error(message) {}
