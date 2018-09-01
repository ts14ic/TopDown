#pragma once

#include "engine/audio/Music.h"
#include <string>
#include <memory>
#include <SDL_mixer.h>

class SdlMusic : public Music {
public:
    SdlMusic();

    struct MixDeleter {
        void operator()(Mix_Music* p);
    };

    explicit SdlMusic(std::unique_ptr<Mix_Music, MixDeleter> music);

    SdlMusic(const SdlMusic&) = delete;

    SdlMusic(SdlMusic&&) noexcept;

    bool is_loaded() const override;

    Mix_Music* get_wrapped_music() const;

private:
    std::unique_ptr<Mix_Music, MixDeleter> _music;
};

