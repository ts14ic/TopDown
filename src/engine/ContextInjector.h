//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include <memory>

class Engine;

class ContextInjector {
public:
    virtual ~ContextInjector() = 0;

    virtual void inject(Engine& engine, int screenWidth, int screenHeight) = 0;
};
