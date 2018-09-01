#pragma once

#include <SDL_mixer.h>
#include <memory>

class SdlMusic {
public:
    SdlMusic();

    struct MixDeleter {
        void operator()(Mix_Music* p);
    };

    explicit SdlMusic(std::unique_ptr<Mix_Music, MixDeleter> music);

    SdlMusic(const SdlMusic&) = delete;

    SdlMusic(SdlMusic&&) noexcept;

    bool is_loaded() const;

    Mix_Music* get_wrapped_music() const;

private:
    std::unique_ptr<Mix_Music, MixDeleter> _music;
};

