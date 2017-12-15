//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../state/GameState.h"
#include <string>

class Engine;

class StateIntro : public GameState {
public:
    explicit StateIntro(Engine& engine);

    void handleWindowEvent(const WindowEvent& event) override;

    void handleMouseEvent(const MouseEvent& event) override;

    void handleKeyEvent(const KeyboardEvent& event) override;

    void handleLogic() override;

    void handleRender() override;

private:
    Engine& mEngine;
    std::string mBackgroundTexId;
};

