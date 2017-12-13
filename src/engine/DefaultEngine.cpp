//
// Created by ts14ic on 12/2/17.
//

#include "DefaultEngine.h"
#include "ContextFactory.h"
#include "../state/StateIntro.h"
#include "../state/StateMoon.h"
#include <SDL_timer.h>

constexpr int MS_ONE_SECOND = 1000;
constexpr int FRAMES_PER_SECOND = 60;
constexpr int MS_PER_FRAME = MS_ONE_SECOND / FRAMES_PER_SECOND;

DefaultEngine::DefaultEngine(
        std::unique_ptr<ContextFactory> contextFactory,
        std::unique_ptr<Random> random)
        : mAssets(std::move(contextFactory->createAssets())),
          mRenderContext{std::move(contextFactory->createRenderContext(800, 600))},
          mAudioContext{std::move(contextFactory->createAudioContext())},
          mInputContext{std::move(contextFactory->createInputContext())},
          mRandom{std::move(random)} {

    getAssets().setRenderContext(getRenderContext());
    getAssets().setAudioContext(getAudioContext());

    loadMedia();
}

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
    return *mInputContext;
}

GraphicContext& DefaultEngine::getRenderContext() {
    return *mRenderContext;
}

Assets& DefaultEngine::getAssets() {
    return *mAssets;
}

Random& DefaultEngine::getRandom() {
    return *mRandom;
}
