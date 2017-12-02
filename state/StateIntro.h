//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../Texture.h"
#include "../engine/Engine.h"

class StateIntro : public GameState {
public:
    explicit StateIntro(RenderSystem& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(RenderSystem& engine) override;

private:
    Texture _background;
};

