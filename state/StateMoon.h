//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../StopWatch.h"
#include "../GameObject.h"
#include "../engine/Engine.h"

class StateMoon : public GameState {
public:
    explicit StateMoon(RenderSystem& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(RenderSystem& engine) override;

    void restrict_pos(Object&);

private:
    Texture _texBackground;
    int const _levelWidth = 800;
    int const _levelHeight = 600;

    Player _pl;
    StopWatch _mobSpawner;
};
