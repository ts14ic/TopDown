#pragma once

#include <SDL_mixer.h>
#include <memory>

class SdlSound {
public:
    SdlSound();

    struct MixDeleter;

    explicit SdlSound(std::unique_ptr<Mix_Chunk, MixDeleter> chunk);

    SdlSound(const SdlSound&) = delete;

    SdlSound(SdlSound&&) noexcept;

    bool is_loaded() const;

    Mix_Chunk* get_wrapped_chunk() const;

    struct MixDeleter {
        void operator()(Mix_Chunk* p);
    };

private:
    std::unique_ptr<Mix_Chunk, MixDeleter> _chunk;
};
