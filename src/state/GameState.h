#pragma once

#include "../event/EventHandler.h"

class Engine;

class GameState : public EventHandler {
public:
    ~GameState() override = 0;

    virtual void handleLogic()  = 0;

    virtual void handleRender() = 0;
};
