//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../assets/Assets.h"
#include "../assets/Music.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include <unordered_map>

class SdlGraphicContext;

class SdlAudioContext;

class SdlAssets : public Assets {
public:
    void setRenderContext(GraphicContext& graphicContext) override;

    void setAudioContext(AudioContext& audioContext) override;

    Texture& getTexture(std::string const& name) override;

    void loadTexture(std::string const& name, const char* path) override;

    Sound& getSound(std::string const& name) override;

    void loadSound(std::string const& name, const char* path) override;

    Music& music(std::string const& name) override;

private:
    SdlGraphicContext* mRenderContext = nullptr;
    SdlAudioContext* mAudioContext = nullptr;
    std::unordered_map<std::string, SdlSound> mNameToSound;
    std::unordered_map<std::string, SdlTexture> mNameToTexture;
    std::unordered_map<std::string, Music> mNameToMusic;
};
