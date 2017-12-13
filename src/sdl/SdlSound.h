//
// Created by ts14ic on 12/13/17.
//

#pragma once


#include "../assets/Sound.h"
#include <memory>

struct Mix_Chunk;

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
