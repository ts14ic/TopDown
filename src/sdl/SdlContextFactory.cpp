//
// Created by ts14ic on 12/13/17.
//

#include "SdlContextFactory.h"
#include "SdlRenderContext.h"
#include "SdlInputContext.h"
#include "SdlAssets.h"

std::unique_ptr<RenderContext> SdlContextFactory::createRenderContext(int screenWidth, int screenHeight) {
    return std::make_unique<SdlRenderContext>(screenWidth, screenHeight);
}

std::unique_ptr<InputContext> SdlContextFactory::createInputContext() {
    return std::make_unique<SdlInputContext>();
}

std::unique_ptr<Assets> SdlContextFactory::createAssets() {
    return std::make_unique<SdlAssets>();
}
