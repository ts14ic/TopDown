//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "RenderSystem.h"
#include "../state/GameState.h"
#include "InputSystem.h"
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

    InputSystem& getInputSystem();

    RenderSystem& getRenderSystem();

private:
    void changeState();

private:
    GState mCurrentStateId;
    GState mNextStateId;
    std::unique_ptr<GameState> mCurrentState;
    StopWatch mFpsWatch;

    RenderSystem mRenderSystem;
    InputSystem mInputSystem;
};
