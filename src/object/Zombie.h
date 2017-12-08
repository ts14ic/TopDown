//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include <vector>
#include "../timer/StopWatch.h"
#include "../engine/RenderContext.h"
#include "Damageable.h"

class Zombie : public Damageable {
public:
    Zombie(int x, int y);

    // GameObject legacy
    float x() const override;

    float y() const override;

    void x(float x) override;

    void y(float y) override;

    float angle() const override;

    float speed() const override;

    void angle(float a) override;

    void speed(float s) override;

    Circle circle() const override;

    std::string texName() const override;

    // Damageable legacy
    int hp() const override;

    int defaultHp() const override;

    bool dead() const override;

    int dmg() const override;

    void damage(int d) override;

    // StateMoon interface
    void set_target(float x, float y, bool ignore = false);

    void handle_logic();

    void handle_render(Assets& assets, RenderContext& renderContext);

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
