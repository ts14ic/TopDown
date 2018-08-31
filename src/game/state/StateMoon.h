#pragma once

#include "GameState.h"
#include "game/object/Player.h"
#include "game/object/GameObject.h"
#include "engine/Engine.h"
#include "engine/Timer.h"

class StateMoon : public GameState {
public:
    explicit StateMoon(Engine& engine);

    StateMoon(const StateMoon& other);

    void handleWindowEvent(const WindowEvent& event) override;

    void handleMouseEvent(const MouseEvent& event) override;

    void handleKeyEvent(const KeyboardEvent& event) override;

    void handleLogic() override;

    void handleRender(float predictionRatio) override;

    void restrict_pos(GameObject&);

private:
    void parseLevelData();

private:
    Engine& mEngine;

    std::string mBackgroundTexId;
    int const _levelWidth;
    int const _levelHeight;

    int mMouseX;
    int mMouseY;
    Player mPlayer;
    Timer mEnemySpawnCooldown;
};
