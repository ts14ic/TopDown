//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "GState.h"
#include "RenderContext.h"
#include "InputContext.h"
#include "../assets/Assets.h"
#include "../state/GameState.h"
#include "../timer/StopWatch.h"

class Engine {
public:
    Engine();

    void runLoop();

    void requestStateChange(GState stateId);

    InputContext& getInputContext();

    RenderContext& getRenderContext();

    Assets& getAssets();

private:
    void changeState();

private:
    GState mCurrentStateId = GState::null;
    GState mNextStateId = GState::null;
    std::unique_ptr<GameState> mCurrentState;
    StopWatch mFpsWatch;

    Assets mAssets;
    RenderContext mRenderSystem;
    InputContext mInputSystem;
};
