//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../resources/Music.h"
#include <string>
#include <memory>

typedef struct _Mix_Music Mix_Music;

class SdlMusic : public Music {
public:
    struct MixDeleter {
        void operator()(Mix_Music* p);
    };

    SdlMusic();

    explicit SdlMusic(std::unique_ptr<Mix_Music, MixDeleter> music);

    SdlMusic(SdlMusic const&) = delete;

    SdlMusic(SdlMusic&&) noexcept;

    bool isLoaded() const override;

    Mix_Music* getWrappedMusic() const;

private:
    std::unique_ptr<Mix_Music, MixDeleter> mMusic;
};

