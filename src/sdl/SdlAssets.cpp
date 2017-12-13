//
// Created by ts14ic on 12/13/17.
//

#include "SdlAssets.h"
#include "SdlGraphicContext.h"

void SdlAssets::setRenderContext(GraphicContext& graphicContext) {
    mRenderContext = dynamic_cast<SdlGraphicContext*>(&graphicContext);
    if(mRenderContext == nullptr) {
        throw std::runtime_error{"SdlAssets can only work with SdlGraphicContext"};
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
    mNameToTexture.insert(std::make_pair(name, std::move(mRenderContext->loadTexture(path))));
}
