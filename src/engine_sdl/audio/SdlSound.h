#pragma once

#include <SDL_mixer.h>
#include <memory>

class SdlSound {
public:
    struct MixDeleter {
        void operator()(Mix_Chunk* p);
    };

    SdlSound();

    explicit SdlSound(std::unique_ptr<Mix_Chunk, MixDeleter> chunk);

    SdlSound(const SdlSound&) = delete;

    SdlSound(SdlSound&&) noexcept;

    bool is_loaded() const;

    Mix_Chunk* get_wrapped_chunk() const;

private:
    std::unique_ptr<Mix_Chunk, MixDeleter> _chunk;
};
