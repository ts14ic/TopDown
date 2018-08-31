#pragma once

#include "engine/audio/Music.h"
#include <string>
#include <memory>
#include <SDL_mixer.h>

class SdlMusic : public Music {
public:
    struct MixDeleter {
        void operator()(Mix_Music* p);
    };

    SdlMusic();

    explicit SdlMusic(std::unique_ptr<Mix_Music, MixDeleter> music);

    SdlMusic(SdlMusic const&) = delete;

    SdlMusic(SdlMusic&&) noexcept;

    bool is_loaded() const override;

    Mix_Music* get_wrapped_music() const;

private:
    std::unique_ptr<Mix_Music, MixDeleter> _music;
};

