#pragma once

#include "engine/ContextInjector.h"

class SdlContextInjector : public ContextInjector {
public:
    void inject(Game& engine, int screenWidth, int screenHeight) override;
};
