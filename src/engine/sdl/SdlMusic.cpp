//
// Created by ts14ic on 12/13/17.
//

#include "SdlMusic.h"
#include <SDL_mixer.h>

SdlMusic::SdlMusic() = default;

SdlMusic::SdlMusic(SdlMusic&&) noexcept = default;

void SdlMusic::MixDeleter::operator()(Mix_Music* p) {
    Mix_FreeMusic(p);
}

SdlMusic::SdlMusic(std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> music)
        : mMusic{std::move(music)} {
}

bool SdlMusic::isLoaded() const {
    return mMusic != nullptr;
}

Mix_Music* SdlMusic::getWrappedMusic() const {
    return mMusic.get();
}
