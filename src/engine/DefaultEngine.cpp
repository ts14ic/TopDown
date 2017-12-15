//
// Created by ts14ic on 12/2/17.
//

#include "DefaultEngine.h"
#include "ContextInjector.h"
#include "../state/StateIntro.h"
#include "../state/StateMoon.h"
#include "../event/WindowEvent.h"
#include "../event/KeyboardEvent.h"
#include <SDL_timer.h>

constexpr unsigned MS_ONE_SECOND = 1000;
constexpr unsigned FRAMES_PER_SECOND = 60;
constexpr unsigned MS_PER_FRAME = MS_ONE_SECOND / FRAMES_PER_SECOND;

DefaultEngine::DefaultEngine(
        int screenWidth, int screenHeight,
        // TODO don't pass a unique_ptr here
        std::unique_ptr<ContextInjector> contextInjector) {
    contextInjector->inject(*this, screenWidth, screenHeight);

    loadResources();
}

void DefaultEngine::runLoop() {
    mCurrentState = std::make_unique<StateIntro>(*this);

    while(mCurrentStateId != GState::exit) {
        mLoopTimer.restart(getClock());

        mInputContext->pollEvents(*this);

        mCurrentState->handleLogic();

        changeState();

        mCurrentState->handleRender();

        if(!mLoopTimer.haveTicksPassedSinceStart(getClock(), MS_PER_FRAME)) {
            // todo Don't call SDL directly
            SDL_Delay(static_cast<unsigned>(MS_PER_FRAME - mLoopTimer.getTicksSinceRestart(getClock())));
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

GraphicContext& DefaultEngine::getGraphicContext() {
    return *mGraphicContext;
}

Resources& DefaultEngine::getResources() {
    return *mResources;
}

Random& DefaultEngine::getRandom() {
    return *mRandom;
}

const Clock& DefaultEngine::getClock() {
    return mResources->getClock();
}

void DefaultEngine::setInputContext(std::unique_ptr<InputContext> inputContext) {
    mInputContext = std::move(inputContext);
}

void DefaultEngine::setGraphicContext(std::unique_ptr<GraphicContext> graphicContext) {
    mGraphicContext = std::move(graphicContext);
}

void DefaultEngine::setAudioContext(std::unique_ptr<AudioContext> audioContext) {
    mAudioContext = std::move(audioContext);
}

void DefaultEngine::setResources(std::unique_ptr<Resources> resources) {
    mResources = std::move(resources);
}

void DefaultEngine::setRandom(std::unique_ptr<Random> random) {
    mRandom = std::move(random);
}

void DefaultEngine::handleWindowEvent(const WindowEvent& event) {
    switch(event.getType()) {
        case WindowEvent::Type::Close: {
            requestStateChange(GState::exit);
            break;
        }

//        default: {
//            mCurrentState->handleWindowEvent(event);
//            break;
//        }
    }
}

void DefaultEngine::handleKeyEvent(const KeyboardEvent& event) {
    mCurrentState->handleKeyEvent(event);
}

void DefaultEngine::handleMouseEvent(const MouseEvent& event) {
    mCurrentState->handleMouseEvent(event);
}
