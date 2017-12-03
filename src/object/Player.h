//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../timer/StopWatch.h"
#include "Damageable.h"
#include "Weapon.h"

class Player : public virtual GameObject, public Damageable {
public:
    Player(int x, int y);

    float x() const override;

    float y() const override;

    float angle() const override;

    float speed() const override;

    void x(float x) override;

    void y(float y) override;

    void angle(float a) override;

    void speed(float s) override;

    Circle circle() const override;

    std::string texName() const override;

    int hp() const override;

    int defaultHp() const override;

    int dmg() const override;

    bool dead() const override;

    void damage(int v) override;

    bool reloading() const;

    void handle_events(InputContext& input);

    void handle_logic();

    void handle_render(RenderContext& engine);

private:
    float _x, _y, _speed;
    float _angle = 0.0f;

    std::unique_ptr<Weapon> _weapons[WEAPON_TOTAL];
    int _currentWeap = WEAPON_PISTOL;
    int _hp;

    StopWatch _dmgCd;

    enum {
        IDLE = 0x0,
        MOVES_UP = 0x1,
        MOVES_DOWN = 0x2,
        MOVES_LEFT = 0x4,
        MOVES_RIGHT = 0x8,
        SHOOTS = 0x10
    };
    int _state = IDLE;
};
