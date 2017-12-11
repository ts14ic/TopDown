#pragma once

#include <memory>

class Engine;

class GameState {
public:
    virtual void handle_events(Engine& engine) = 0;

    virtual void handle_logic(Engine& engine)  = 0;

    virtual void handle_render(Engine& engine) = 0;

    virtual ~GameState() = default;
};
