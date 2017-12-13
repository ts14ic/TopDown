//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "Engine.h"
#include "GState.h"
#include "../state/GameState.h"
#include "../timer/StopWatch.h"
#include "../assets/Assets.h"
#include "GraphicContext.h"
#include "InputContext.h"
#include "AudioContext.h"
#include "Random.h"
#include <memory>

class ContextFactory;

class DefaultEngine : public Engine {
public:
    DefaultEngine(
            std::unique_ptr<ContextFactory> contextFactory,
            std::unique_ptr<Random> random
    );

    void runLoop() override;

    void requestStateChange(GState stateId) override;

    InputContext& getInputContext() override;

    GraphicContext& getRenderContext() override;

    AudioContext& getAudioContext() override;

    Assets& getAssets() override;

    Random& getRandom() override;

private:
    void changeState();

    void loadMedia();

private:
    GState mCurrentStateId = GState::null;
    GState mNextStateId = GState::null;
    std::unique_ptr<GameState> mCurrentState;
    StopWatch mFpsWatch;

    std::unique_ptr<Assets> mAssets;
    std::unique_ptr<GraphicContext> mRenderContext;
    std::unique_ptr<AudioContext> mAudioContext;
    std::unique_ptr<InputContext> mInputContext;
    std::unique_ptr<Random> mRandom;
};
