#pragma once

#include "engine/ContextInjector.h"

class SdlContextInjector : public ContextInjector {
public:
    void inject(Engine& engine, int screenWidth, int screenHeight) override;
};
