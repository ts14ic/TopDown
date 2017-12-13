//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../assets/Assets.h"
#include "../assets/Music.h"
#include "SdlTexture.h"
#include "SdlSound.h"
#include "SdlMusic.h"
#include <unordered_map>

class SdlGraphicContext;

class SdlAudioContext;

class SdlAssets : public Assets {
public:
    void setRenderContext(GraphicContext& graphicContext) override;

    void setAudioContext(AudioContext& audioContext) override;

    Texture& getTexture(const std::string& name) override;

    void loadTexture(const std::string& name, const char* path) override;

    Sound& getSound(const std::string& name) override;

    void loadSound(const std::string& name, const char* path) override;

    Music& getMusic(const std::string& name) override;

    void loadMusic(const std::string& name, const char* path) override;

private:
    SdlGraphicContext* mRenderContext = nullptr;
    SdlAudioContext* mAudioContext = nullptr;
    std::unordered_map<std::string, SdlSound> mNameToSound;
    std::unordered_map<std::string, SdlTexture> mNameToTexture;
    std::unordered_map<std::string, SdlMusic> mNameToMusic;
};
