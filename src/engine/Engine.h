//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "RenderContext.h"
#include "../state/GameState.h"
#include "InputContext.h"
#include "../timer/StopWatch.h"
#include "../assets/Assets.h"

enum class GState {
    null,
    intro,
    moon,
    score,
    exit
};

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
