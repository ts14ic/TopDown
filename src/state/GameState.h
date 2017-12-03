#pragma once

#include "../texture/Texture.h"
#include "../object/GameObject.h"
#include <memory>

// forward declarations begin
class Engine;
// forward declarations end

class GameState {
public:
    virtual void handle_events(Engine& engine) = 0;

    virtual void handle_logic(Engine& engine)  = 0;

    virtual void handle_render(Engine& engine) = 0;

    virtual ~GameState() = default;
};

