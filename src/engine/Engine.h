#pragma once

#include "input/InputContext.h"
#include "graphic/GraphicContext.h"
#include "AudioContext.h"
#include "resources/Resources.h"
#include "Random.h"
#include "Clock.h"
#include "GState.h"
#include <memory>

class Engine {
public:
    virtual ~Engine();

    virtual void runLoop() = 0;

    virtual void requestStateChange(GState stateId) = 0;

    virtual GraphicContext& getGraphicContext() = 0;

    virtual AudioContext& getAudioContext() = 0;

    virtual Resources& getResources() = 0;

    virtual Random& getRandom() = 0;

    virtual const Clock& getClock() = 0;

    virtual void setInputContext(std::unique_ptr<InputContext> inputContext) = 0;

    virtual void setGraphicContext(std::unique_ptr<GraphicContext> graphicContext) = 0;

    virtual void setAudioContext(std::unique_ptr<AudioContext> audioContext) = 0;

    virtual void setResources(std::unique_ptr<Resources> resources) = 0;

    virtual void setRandom(std::unique_ptr<Random> random) = 0;
};
