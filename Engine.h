//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "RenderBase.h"
#include "state/GameState.h"

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

private:
    void changeState();

private:
    GState mCurrentStateId;
    GState mNextStateId;
    std::unique_ptr<GameState> mCurrentState;
    StopWatch mFpsWatch;

    RenderBase mRenderBase;
};
