#pragma once

#include "../event/EventHandler.h"

class Engine;

class GameState : public EventHandler {
public:
    virtual void handle_logic(Engine &engine)  = 0;

    virtual void handle_render(Engine &engine) = 0;
};
