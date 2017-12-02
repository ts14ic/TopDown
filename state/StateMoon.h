//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../StopWatch.h"
#include "../object/GameObject.h"
#include "../engine/Engine.h"
#include "../object/Player.h"

class StateMoon : public GameState {
public:
    explicit StateMoon(Engine& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(Engine& engine) override;

    void restrict_pos(GameObject&);

private:
    Texture _texBackground;
    int const _levelWidth = 800;
    int const _levelHeight = 600;

    Player _pl;
    StopWatch _mobSpawner;
};
