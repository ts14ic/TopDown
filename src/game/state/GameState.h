#pragma once

#include <engine/input/EventHandler.h>

class GameState : public EventHandler {
public:
    ~GameState() override = 0;

    virtual void handle_logic()  = 0;

    virtual void handle_render(float frames_count) = 0;
};
