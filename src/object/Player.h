//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "Damageable.h"
#include "../timer/StopWatch.h"
#include "Weapon.h"
#include <memory>
#include <bitset>

class InputContext;


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

    void handle_logic(Assets& assets);

    void handle_render(Assets& assets, RenderContext& renderContext);

private:
    void selectNextWeapon();

    void selectPreviousWeapon();

    void selectWeapon(int idx);

private:
    float _x = 0, _y = 0, _speed = 0;
    float _angle = 0.0f;

    std::vector<Weapon> mWeapons;
    int mSelectedWeaponIdx = 0;
    int _hp = 0;

    StopWatch _dmgCd;

    enum InputState {
        UP_PRESSED,
        DOWN_PRESSED,
        LEFT_PRESSED,
        RIGHT_PRESSED,
        TRIGGER_PRESSED,
        LENGTH
    };
    std::bitset<LENGTH> mInputState;
};
