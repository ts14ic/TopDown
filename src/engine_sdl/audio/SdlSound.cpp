#include "SdlSound.h"

void ChunkDeleter::operator()(Mix_Chunk* p) {
    Mix_FreeChunk(p);
}

SdlSound::SdlSound() = default;

SdlSound::SdlSound(ChunkHandle chunk)
        : _chunk{std::move(chunk)} {

}

SdlSound::SdlSound(SdlSound&&) noexcept = default;

bool SdlSound::is_loaded() const {
    return _chunk != nullptr;
}

Mix_Chunk* SdlSound::get_wrapped_chunk() const {
    return _chunk.get();
}
