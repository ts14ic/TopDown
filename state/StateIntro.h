//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../Texture.h"
#include "../Engine.h"

class StateIntro : public GameState {
public:
    explicit StateIntro(RenderBase& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(RenderBase& engine) override;

private:
    Texture _background;
};

