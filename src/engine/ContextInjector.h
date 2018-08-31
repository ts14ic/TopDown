#pragma once

#include "Engine.h"
#include <memory>

class ContextInjector {
public:
    virtual ~ContextInjector() = 0;

    virtual void inject(Engine& engine, int screenWidth, int screenHeight) = 0;
};
