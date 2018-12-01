#pragma once

#include <engine/input/EventHandler.h>

class GameState : public EventHandler {
public:
    ~GameState() override = 0;

    virtual void handle_logic() = 0;

    virtual void handle_render(float milliseconds_passed, float milliseconds_per_frame) = 0;
};
