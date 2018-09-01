#include "SdlMusic.h"

SdlMusic::SdlMusic() = default;

SdlMusic::SdlMusic(SdlMusic&&) noexcept = default;

void SdlMusic::MixDeleter::operator()(Mix_Music* p) {
    Mix_FreeMusic(p);
}

SdlMusic::SdlMusic(std::unique_ptr<Mix_Music, SdlMusic::MixDeleter> music)
        : _music{std::move(music)} {
}

bool SdlMusic::is_loaded() const {
    return _music != nullptr;
}

Mix_Music* SdlMusic::get_wrapped_music() const {
    return _music.get();
}
