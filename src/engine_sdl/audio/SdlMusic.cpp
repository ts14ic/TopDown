#include "SdlMusic.h"

void MusicDeleter::operator()(Mix_Music* p) {
    Mix_FreeMusic(p);
}

SdlMusic::SdlMusic() = default;

SdlMusic::SdlMusic(SdlMusic&&) noexcept = default;

SdlMusic::SdlMusic(MusicHandle music)
        : _music{std::move(music)} {
}

bool SdlMusic::is_loaded() const {
    return _music != nullptr;
}

Mix_Music* SdlMusic::get_wrapped_music() const {
    return _music.get();
}
