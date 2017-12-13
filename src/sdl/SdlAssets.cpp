//
// Created by ts14ic on 12/13/17.
//

#include "SdlAssets.h"
#include "SdlRenderContext.h"

void SdlAssets::setRenderContext(RenderContext& renderContext) {
    mRenderContext = dynamic_cast<SdlRenderContext*>(&renderContext);
    if(mRenderContext == nullptr) {
        throw std::runtime_error{"SdlAssets can only work with SdlRenderContext"};
    }
}

Texture& SdlAssets::getTexture(std::string const& name) {
    return mNameToTexture[name];
}

Music& SdlAssets::music(std::string const& name) {
    return mNameToMusic[name];
}

Sound& SdlAssets::sound(std::string const& name) {
    return mNameToSound[name];
}

void SdlAssets::loadTexture(std::string const& name, const char* path) {
    getTexture(name).load(*mRenderContext, path);
}
