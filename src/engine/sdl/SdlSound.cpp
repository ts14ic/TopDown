//
// Created by ts14ic on 12/13/17.
//

#include "SdlSound.h"
#include <SDL_mixer.h>

SdlSound::SdlSound() = default;

SdlSound::SdlSound(std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> chunk)
        : mChunk{std::move(chunk)} {

}

SdlSound::SdlSound(SdlSound&&) noexcept = default;

void SdlSound::MixDeleter::operator()(Mix_Chunk* p) {
    Mix_FreeChunk(p);
}

bool SdlSound::isLoaded() const {
    return mChunk != nullptr;
}

Mix_Chunk* SdlSound::getWrappedChunk() const {
    return mChunk.get();
}
