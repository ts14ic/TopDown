//
// Created by ts14ic on 12/3/17.
//

#include <SDL_mixer.h>
#include <SDL_log.h>
#include <unordered_map>
#include "Music.h"

Music::Music() = default;

Music::Music(char const* path) {
    load(path);
}

void Music::load(char const* path) {
    mMusic.reset(Mix_LoadMUS(path));
    if(!mMusic) {
        throw FailedToLoadMusicException{Mix_GetError()};
    }
    SDL_Log("Music loaded: %s.\n", path);
}

void Music::play() const {
    if(mMusic && Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(mMusic.get(), -1);
    }
}

Music& music(std::string const& name) {
    static std::unordered_map<std::string, Music> ret;
    return ret[name];
}

Music::FailedToLoadMusicException::FailedToLoadMusicException(const char* message) : runtime_error(message) {}

void Music::MixDeleter::operator()(Mix_Music* p) {
    Mix_FreeMusic(p);
}
