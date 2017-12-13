//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "Engine.h"
#include "GState.h"
#include "RenderContext.h"
#include "InputContext.h"
#include "../assets/Assets.h"
#include "../state/GameState.h"
#include "../timer/StopWatch.h"
#include "Random.h"
#include <memory>

class DefaultEngine : public Engine {
public:
    explicit DefaultEngine(std::unique_ptr<InputContext> inputContext);

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

    Random mRandom;
    Assets mAssets;
    RenderContext mRenderSystem;
    std::unique_ptr<InputContext> mInputContext;
};
