//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../state/GameState.h"
#include "../object/Player.h"
#include "../engine/Timer.h"

class Engine;

class GameObject;

class StateMoon : public GameState {
public:
    explicit StateMoon(Engine& engine);

    virtual void handleWindowEvent() override;

    void handle_logic(Engine& engine) override;

    void handle_render(Engine& engine) override;

    void restrict_pos(GameObject&);

private:
    void parseLevelData();

private:
    std::string mBackgroundTexId;
    int const _levelWidth;
    int const _levelHeight;

    Player mPlayer;
    Timer mEnemySpawnCooldown;
};
