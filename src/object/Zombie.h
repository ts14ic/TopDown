//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "Damageable.h"
#include "../timer/StopWatch.h"
#include <vector>

class GraphicContext;

class Zombie : public Damageable {
public:
    Zombie(int x, int y);

    // GameObject legacy
    float getX() const override;

    float getY() const override;

    void setX(float x) override;

    void setY(float y) override;

    void setPos(float x, float y) override;

    float getAngle() const override;

    float getSpeed() const override;

    void setAngle(float angle) override;

    void setSpeed(float speed) override;

    Circle getCircle() const override;

    std::string getTexName() const override;

    // Damageable legacy
    int hp() const override;

    int defaultHp() const override;

    bool dead() const override;

    int dmg() const override;

    void damage(int d) override;

    // StateMoon interface
    void set_target(float x, float y, bool ignore = false);

    void handle_logic();

    void handle_render(Assets& assets, GraphicContext& graphicContext);

private:
    float _x, _y;
    float _angle;
    float _speed = 1.7f;

    int _hp, _frame = 0;

    StopWatch _timer;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        DYING = 0x4
    };
    int _state = IDLE;
};

std::vector<Zombie>& zombies();
