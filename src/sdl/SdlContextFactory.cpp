//
// Created by ts14ic on 12/13/17.
//

#include "SdlContextFactory.h"
#include "SdlGraphicContext.h"
#include "SdlAudioContext.h"
#include "SdlInputContext.h"
#include "SdlResources.h"

std::unique_ptr<GraphicContext> SdlContextFactory::createRenderContext() {
    return std::make_unique<SdlGraphicContext>();
}

std::unique_ptr<InputContext> SdlContextFactory::createInputContext() {
    return std::make_unique<SdlInputContext>();
}

std::unique_ptr<Resources> SdlContextFactory::createResources(int screenWidth, int screenHeight) {
    return std::make_unique<SdlResources>(screenWidth, screenHeight);
}

std::unique_ptr<AudioContext> SdlContextFactory::createAudioContext() {
    return std::make_unique<SdlAudioContext>();
}
