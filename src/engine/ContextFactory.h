//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include <memory>

class RenderContext;

class InputContext;

class Assets;

class ContextFactory {
public:
    virtual std::unique_ptr<RenderContext> createRenderContext(int screenWidth, int screenHeight) = 0;

    virtual std::unique_ptr<InputContext> createInputContext() = 0;

    virtual std::unique_ptr<Assets> createAssets() = 0;

    virtual ~ContextFactory() = 0;
};
