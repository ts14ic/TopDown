//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "GameState.h"
#include "engine/Engine.h"
#include <string>

class StateIntro : public GameState {
public:
    explicit StateIntro(Engine& engine);

    void handleWindowEvent(const WindowEvent& event) override;

    void handleMouseEvent(const MouseEvent& event) override;

    void handleKeyEvent(const KeyboardEvent& event) override;

    void handleLogic() override;

    void handleRender(float predictionRatio) override;

private:
    Engine& mEngine;
    std::string mBackgroundTexId;
};

