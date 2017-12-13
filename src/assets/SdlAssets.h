//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "Assets.h"
#include "../sdl/Texture.h"
#include "../sdl/Music.h"
#include "../sdl/Sound.h"
#include <unordered_map>

class SdlAssets : public Assets {
public:
    Texture& texture(std::string const& name) override;

    Music& music(std::string const& name) override;

    Sound& sound(std::string const& name) override;

private:
    std::unordered_map<std::string, Music> mNameToMusic;
    std::unordered_map<std::string, Sound> mNameToSound;
    std::unordered_map<std::string, Texture> mNameToTexture;
};
