#pragma once

#include "engine/input/EventHandler.h"

class GameState : public EventHandler {
public:
    ~GameState() override = 0;

    virtual void handle_logic()  = 0;

    virtual void handle_render(float prediction_ratio) = 0;
};
