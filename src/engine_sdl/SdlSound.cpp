#include "SdlSound.h"

SdlSound::SdlSound() = default;

SdlSound::SdlSound(std::unique_ptr<Mix_Chunk, SdlSound::MixDeleter> chunk)
        : _chunk{std::move(chunk)} {

}

SdlSound::SdlSound(SdlSound&&) noexcept = default;

void SdlSound::MixDeleter::operator()(Mix_Chunk* p) {
    Mix_FreeChunk(p);
}

bool SdlSound::is_loaded() const {
    return _chunk != nullptr;
}

Mix_Chunk* SdlSound::get_wrapped_chunk() const {
    return _chunk.get();
}
