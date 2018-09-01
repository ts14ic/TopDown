#pragma once

#include <SDL_mixer.h>
#include <memory>

struct ChunkDeleter {
    void operator()(Mix_Chunk* p);
};

using ChunkHandle = std::unique_ptr<Mix_Chunk, ChunkDeleter>;

class SdlSound {
public:
    SdlSound();

    explicit SdlSound(ChunkHandle chunk);

    SdlSound(const SdlSound&) = delete;

    SdlSound(SdlSound&&) noexcept;

    bool is_loaded() const;

    Mix_Chunk* get_wrapped_chunk() const;

private:
    ChunkHandle _chunk;
};
