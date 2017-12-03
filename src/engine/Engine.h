//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "RenderContext.h"
#include "../state/GameState.h"
#include "InputContext.h"
#include "../timer/StopWatch.h"

enum class GState {
    null,
    intro,
    moon,
    score,
    exit
};

class Engine {
public:
    void runLoop();

    void requestStateChange(GState stateId);

    InputContext& getInputContext();

    RenderContext& getRenderContext();

private:
    void changeState();

private:
    GState mCurrentStateId;
    GState mNextStateId;
    std::unique_ptr<GameState> mCurrentState;
    StopWatch mFpsWatch;

    RenderContext mRenderSystem;
    InputContext mInputSystem;
};
