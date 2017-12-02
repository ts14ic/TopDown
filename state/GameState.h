#pragma once

#include "../Texture.h"
#include "../GameObject.h"
#include <memory>

// forward declarations begin
union SDL_Event;

class Engine;
// forward declarations end

SDL_Event& gameEvent();

class GameState {
public:
    virtual void handle_events(Engine& engine) = 0;

    virtual void handle_logic(Engine& engine)  = 0;

    virtual void handle_render(RenderSystem& engine) = 0;

    virtual ~GameState() = default;
};

