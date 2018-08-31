#pragma once

#include "game/Game.h"
#include <memory>

class ContextInjector {
public:
    virtual ~ContextInjector() = 0;

    virtual void inject(Game& engine, int screenWidth, int screenHeight) = 0;
};
