//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/ContextFactory.h"

class SdlContextFactory : public ContextFactory {
public:
    std::unique_ptr<GraphicContext> createRenderContext() override;

    std::unique_ptr<AudioContext> createAudioContext() override;

    std::unique_ptr<InputContext> createInputContext() override;

    std::unique_ptr<Resources> createResources(int screenWidth, int screenHeight) override;
};
