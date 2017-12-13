//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../assets/Assets.h"
#include "SdlTexture.h"
#include "Music.h"
#include "Sound.h"
#include <unordered_map>

class SdlGraphicContext;

class SdlAssets : public Assets {
public:
    void setRenderContext(GraphicContext& graphicContext) override;

    Texture& getTexture(std::string const& name) override;

    void loadTexture(std::string const& name, const char* path) override;

    Music& music(std::string const& name) override;

    Sound& sound(std::string const& name) override;

private:
    SdlGraphicContext* mRenderContext;
    std::unordered_map<std::string, Music> mNameToMusic;
    std::unordered_map<std::string, Sound> mNameToSound;
    std::unordered_map<std::string, SdlTexture> mNameToTexture;
};
