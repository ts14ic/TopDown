//
// Created by ts14ic on 12/8/17.
//

#pragma once

#include "../texture/Texture.h"
#include "../sound/Music.h"
#include "../sound/Sound.h"
#include <unordered_map>

class Assets {
public:
    Texture& texture(std::string const& name);

    Music& music(std::string const& name);

    Sound& sound(std::string const& name);

private:
    std::unordered_map<std::string, Music> mNameToMusic;
    std::unordered_map<std::string, Sound> mNameToSound;
    std::unordered_map<std::string, Texture> mNameToTexture;
};
