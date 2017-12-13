//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "Engine.h"
#include "GState.h"
#include "RenderContext.h"
#include "InputContext.h"
#include "Random.h"
#include "../assets/Assets.h"
#include "../state/GameState.h"
#include "../timer/StopWatch.h"
#include <memory>

class DefaultEngine : public Engine {
public:
    DefaultEngine(
            Assets& assets,
            std::unique_ptr<RenderContext> renderContext,
            std::unique_ptr<InputContext> inputContext,
            std::unique_ptr<Random> random
    );

    void runLoop() override;

    void requestStateChange(GState stateId) override;

    InputContext& getInputContext() override;

    RenderContext& getRenderContext() override;

    Assets& getAssets() override;

    Random& getRandom() override;

private:
    void changeState();

private:
    GState mCurrentStateId = GState::null;
    GState mNextStateId = GState::null;
    std::unique_ptr<GameState> mCurrentState;
    StopWatch mFpsWatch;

    Assets& mAssets;
    std::unique_ptr<RenderContext> mRenderContext;
    std::unique_ptr<InputContext> mInputContext;
    std::unique_ptr<Random> mRandom;
};
