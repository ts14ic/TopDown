//
// Created by ts14ic on 12/2/17.
//

#include <SDL_timer.h>
#include "Engine.h"

constexpr int MS_ONE_SECOND = 1000;
constexpr int FRAMES_PER_SECOND = 60;
constexpr int MS_PER_FRAME = MS_ONE_SECOND / FRAMES_PER_SECOND;

void Engine::runLoop() {
    mCurrentState = std::make_unique<StateIntro>(mRenderBase);

    while(mCurrentStateId != GState::exit) {
        mFpsWatch.start();

        mCurrentState->handle_events(*this);
        mCurrentState->handle_logic(*this);

        changeState();

        mCurrentState->handle_render(mRenderBase);

        if(mFpsWatch.get_ticks() < MS_PER_FRAME) {
            SDL_Delay(MS_PER_FRAME - mFpsWatch.get_ticks());
        }
    }
}

void Engine::changeState() {
    if(mNextStateId != GState::null) {
        if(mNextStateId != GState::exit) {
            mCurrentState.reset(nullptr);
        }

        switch(mNextStateId) {
            case GState::intro:
                mCurrentState = std::make_unique<StateIntro>(mRenderBase);
                break;

            case GState::moon:
                mCurrentState = std::make_unique<StateMoon>(mRenderBase);
                break;

            default:;
        }

        mCurrentStateId = mNextStateId;
        mNextStateId = GState::null;
    }
}

void Engine::requestStateChange(GState stateId) {
    if(mNextStateId != GState::exit) {
        mNextStateId = stateId;
    }
}
