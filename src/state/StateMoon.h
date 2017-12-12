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

    struct FailedToParseLevelData : public std::runtime_error {
        explicit FailedToParseLevelData(const char* message);

        explicit FailedToParseLevelData(const std::string& message);
    };

private:
    void parseLevelData();

private:
    // todo replace with text path
    Texture _texBackground;
    int const _levelWidth;
    int const _levelHeight;

    Player mPlayer;
    StopWatch _mobSpawner;
};
