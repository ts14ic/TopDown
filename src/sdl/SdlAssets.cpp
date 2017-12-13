//
// Created by ts14ic on 12/13/17.
//

#include "SdlAssets.h"
#include "SdlGraphicContext.h"
#include "SdlAudioContext.h"

void SdlAssets::setRenderContext(GraphicContext& graphicContext) {
    mRenderContext = dynamic_cast<SdlGraphicContext*>(&graphicContext);
    if(mRenderContext == nullptr) {
        throw std::runtime_error{"SdlAssets can only work with SdlGraphicContext"};
    }
}

void SdlAssets::setAudioContext(AudioContext& audioContext) {
    mAudioContext = dynamic_cast<SdlAudioContext*>(&audioContext);
    if(mAudioContext == nullptr) {
        throw std::runtime_error{"SdlAssets can only work with SdlAudioContext"};
    }
}

Texture& SdlAssets::getTexture(std::string const& name) {
    return mNameToTexture[name];
}

Music& SdlAssets::getMusic(std::string const& name) {
    return mNameToMusic[name];
}

Sound& SdlAssets::getSound(std::string const& name) {
    return mNameToSound[name];
}

void SdlAssets::loadTexture(std::string const& name, const char* path) {
    mNameToTexture.insert(std::make_pair(name, std::move(mRenderContext->loadTexture(path))));
}

void SdlAssets::loadSound(std::string const& name, const char* path) {
    mNameToSound.insert(std::make_pair(name, std::move(mAudioContext->loadSound(path))));
}

void SdlAssets::loadMusic(const std::string& name, const char* path) {
    mNameToMusic.insert(std::make_pair(name, std::move(mAudioContext->loadMusic(path))));
}
