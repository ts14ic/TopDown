//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "GState.h"
#include <memory>

class InputContext;

class GraphicContext;

class AudioContext;

class Resources;

class Random;

class Engine {
public:
    virtual void runLoop() = 0;

    virtual void requestStateChange(GState stateId) = 0;

    virtual InputContext& getInputContext() = 0;

    virtual void setInputContext(std::unique_ptr<InputContext> inputContext) = 0;

    virtual GraphicContext& getGraphicContext() = 0;

    virtual void setGraphicContext(std::unique_ptr<GraphicContext> graphicContext) = 0;

    virtual AudioContext& getAudioContext() = 0;

    virtual void setAudioContext(std::unique_ptr<AudioContext> audioContext) = 0;

    virtual Resources& getResources() = 0;

    virtual void setResources(std::unique_ptr<Resources> resources) = 0;

    virtual Random& getRandom() = 0;

    virtual ~Engine();
};
