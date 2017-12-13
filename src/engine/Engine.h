//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "GState.h"

class InputContext;

class GraphicContext;

class AudioContext;

class Assets;

class Random;

class Engine {
public:
    virtual void runLoop() = 0;

    virtual void requestStateChange(GState stateId) = 0;

    virtual InputContext& getInputContext() = 0;

    virtual GraphicContext& getRenderContext() = 0;

    virtual AudioContext& getAudioContext() = 0;

    virtual Assets& getAssets() = 0;

    virtual Random& getRandom() = 0;

    virtual ~Engine();
};
