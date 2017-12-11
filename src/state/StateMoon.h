//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../state/GameState.h"
#include "../texture/Texture.h"
#include "../object/Player.h"
#include "../timer/StopWatch.h"
#include <random>

class Engine;

class GameObject;

class StateMoon : public GameState {
public:
    explicit StateMoon(Engine& engine);

    void handle_events(Engine& engine) override;

    void handle_logic(Engine& engine) override;

    void handle_render(Engine& engine) override;

    void restrict_pos(GameObject&);

private:
    int randomInt();

private:
    std::mt19937 mRandomEngine;
    std::uniform_int_distribution<int> mRandomDistribution;

    // todo replace with text path
    Texture _texBackground;
    int const _levelWidth = 800;
    int const _levelHeight = 600;

    Player _pl;
    StopWatch _mobSpawner;
};
