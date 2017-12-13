//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "Engine.h"
#include "GState.h"
#include "../state/GameState.h"
#include "../timer/StopWatch.h"
#include "../resources/Resources.h"
#include "GraphicContext.h"
#include "InputContext.h"
#include "AudioContext.h"
#include "Random.h"
#include <memory>

class ContextInjector;

class DefaultEngine : public Engine {
public:
    DefaultEngine(
            int screenWidth, int screenHeight,
            std::unique_ptr<ContextInjector> contextInjector,
            std::unique_ptr<Random> random
    );

    void runLoop() override;

    void requestStateChange(GState stateId) override;

    InputContext& getInputContext() override;

    void setInputContext(std::unique_ptr<InputContext> inputContext) override;

    GraphicContext& getGraphicContext() override;

    void setGraphicContext(std::unique_ptr<GraphicContext> graphicContext) override;

    AudioContext& getAudioContext() override;

    void setAudioContext(std::unique_ptr<AudioContext> audioContext) override;

    Resources& getResources() override;

    void setResources(std::unique_ptr<Resources> resources) override;

    Random& getRandom() override;

private:
    void changeState();

    void loadResources();

private:
    // todo add a loop event
    GState mCurrentStateId = GState::null;
    GState mNextStateId = GState::null;
    std::unique_ptr<GameState> mCurrentState;
    StopWatch mFpsWatch;

    std::unique_ptr<Resources> mResources;
    std::unique_ptr<GraphicContext> mGraphicContext;
    std::unique_ptr<AudioContext> mAudioContext;
    std::unique_ptr<InputContext> mInputContext;
    std::unique_ptr<Random> mRandom;
};