#pragma once


#include "engine/resources/Sound.h"
#include <memory>
#include <SDL_mixer.h>

class SdlSound : public Sound {
public:
    struct MixDeleter {
        void operator()(Mix_Chunk* p);
    };

    SdlSound();

    explicit SdlSound(std::unique_ptr<Mix_Chunk, MixDeleter> chunk);

    SdlSound(SdlSound const&) = delete;

    SdlSound(SdlSound&&) noexcept;

    bool isLoaded() const override;

    Mix_Chunk* getWrappedChunk() const;

private:
    std::unique_ptr<Mix_Chunk, MixDeleter> mChunk;
};
