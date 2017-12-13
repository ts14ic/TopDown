//
// Created by ts14ic on 12/2/17.
//

#include "DefaultEngine.h"
#include "../state/StateIntro.h"
#include "../state/StateMoon.h"
#include <SDL_timer.h>

constexpr int MS_ONE_SECOND = 1000;
constexpr int FRAMES_PER_SECOND = 60;
constexpr int MS_PER_FRAME = MS_ONE_SECOND / FRAMES_PER_SECOND;

DefaultEngine::DefaultEngine()
        : mRenderSystem{mAssets, 800, 600} {}

void DefaultEngine::runLoop() {
    mCurrentState = std::make_unique<StateIntro>(*this);

    while(mCurrentStateId != GState::exit) {
        mFpsWatch.restart();

        mCurrentState->handle_events(*this);
        mCurrentState->handle_logic(*this);

        changeState();

        mCurrentState->handle_render(*this);

        if(mFpsWatch.getTicks() < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - mFpsWatch.getTicks());
        }
    }
}

void DefaultEngine::changeState() {
    if(mNextStateId != GState::null) {
        if(mNextStateId != GState::exit) {
            mCurrentState.reset(nullptr);
        }

        switch(mNextStateId) {
            case GState::intro:
                mCurrentState = std::make_unique<StateIntro>(*this);
                break;

            case GState::moon:
                mCurrentState = std::make_unique<StateMoon>(*this);
                break;

            default:;
        }

        mCurrentStateId = mNextStateId;
        mNextStateId = GState::null;
    }
}

void DefaultEngine::requestStateChange(GState stateId) {
    if(mNextStateId != GState::exit) {
        mNextStateId = stateId;
    }
}

InputContext& DefaultEngine::getInputContext() {
    return mInputSystem;
}

RenderContext& DefaultEngine::getRenderContext() {
    return mRenderSystem;
}

Assets& DefaultEngine::getAssets() {
    return mAssets;
}

Random& DefaultEngine::getRandom() {
    return mRandom;
}
