//
// Created by ts14ic on 12/2/17.
//
#pragma once

#include "Engine.h"
#include "GState.h"
#include "../state/GameState.h"
#include "../resources/Resources.h"
#include "../event/InputContext.h"
#include "../event/EventHandler.h"
#include "Timer.h"
#include "Clock.h"
#include "GraphicContext.h"
#include "AudioContext.h"
#include "Random.h"
#include <memory>

class ContextInjector;

class DefaultEngine : public Engine,
                      public EventHandler {
public:
    DefaultEngine(
            int screenWidth, int screenHeight,
            ContextInjector* contextInjector
    );

    void runLoop() override;

    void requestStateChange(GState stateId) override;

    GraphicContext &getGraphicContext() override;

    AudioContext &getAudioContext() override;

    Resources &getResources() override;

    Random &getRandom() override;

    const Clock &getClock() override;

    void handleWindowEvent(const WindowEvent& event) override;

    void handleKeyEvent(const KeyboardEvent& event) override;

    void handleMouseEvent(const MouseEvent& event) override;

    void setInputContext(std::unique_ptr<InputContext> inputContext) override;

    void setGraphicContext(std::unique_ptr<GraphicContext> graphicContext) override;

    void setAudioContext(std::unique_ptr<AudioContext> audioContext) override;

    void setResources(std::unique_ptr<Resources> resources) override;

    void setRandom(std::unique_ptr<Random> random) override;

private:
    void changeState();

    void loadResources();

private:
    // todo add a loop event
    GState mCurrentStateId = GState::null;
    GState mNextStateId = GState::null;
    std::unique_ptr<GameState> mCurrentState;
    Timer mLoopTimer;

    std::unique_ptr<Resources> mResources;
    std::unique_ptr<GraphicContext> mGraphicContext;
    std::unique_ptr<AudioContext> mAudioContext;
    std::unique_ptr<InputContext> mInputContext;
    std::unique_ptr<Random> mRandom;
};
