//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "Damageable.h"
#include "../timer/StopWatch.h"
#include <vector>

class Werewolf : public Damageable {
public:
    Werewolf(float x, float y);

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

    int dmg() const override;

    void damage(int d) override;

    bool dead() const override;

    // StateMoon interface
    void set_target(float x, float y, bool ignore = false);

    void teleport();

    void handle_logic();

    void handle_render(Assets& assets, RenderContext& engine);

private:
    float _x, _y, _speed = 2.5f;
    float _angle = 0.f;
    int _hp;

    int _frame = 0;
    StopWatch _timer;
    StopWatch _teleportCd;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        TELEPORTING = 0x4,
        DYING = 0x8
    };
    int _state = IDLE;
};

std::vector<Werewolf>& werewolves();
