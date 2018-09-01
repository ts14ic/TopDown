#pragma once

#include <SDL_mixer.h>
#include <memory>

struct MusicDeleter {
    void operator()(Mix_Music* p);
};

using MusicHandle = std::unique_ptr<Mix_Music, MusicDeleter>;

class SdlMusic {
public:
    SdlMusic();

    explicit SdlMusic(MusicHandle music);

    SdlMusic(const SdlMusic&) = delete;

    SdlMusic(SdlMusic&&) noexcept;

    bool is_loaded() const;

    Mix_Music* get_wrapped_music() const;

private:
    MusicHandle _music;
};
