//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/ContextInjector.h"

class SdlGraphicContext;

class SdlAudioContext;

class SdlInputContext;

class SdlResources;

class SdlContextInjector : public ContextInjector {
public:
    void inject(Engine& engine, int screenWidth, int screenHeight) override;
};
