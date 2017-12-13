//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../state/GameState.h"
#include "../sdl/Texture.h"

class Engine;

class StateIntro : public GameState {
public:
    explicit StateIntro(Engine& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(Engine& engine) override;

private:
    Texture _background;
};

