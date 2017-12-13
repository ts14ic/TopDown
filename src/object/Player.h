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
    Player();

    Player(int x, int y);

    float getX() const override;

    float getY() const override;

    float getAngle() const override;

    float getSpeed() const override;

    void setPos(float x, float y) override;

    void setX(float x) override;

    void setY(float y) override;

    void setAngle(float a) override;

    void setSpeed(float s) override;

    Circle getCircle() const override;

    std::string getTexName() const override;

    int hp() const override;

    int defaultHp() const override;

    int dmg() const override;

    bool dead() const override;

    void damage(int v) override;

    bool reloading() const;

    void handle_events(InputContext& input);

    void handle_logic(Random& random, Assets& assets);

    void handle_render(Assets& assets, GraphicContext& graphicContext);

    void addWeapon(Weapon weapon);

private:
    void selectNextWeapon();

    void selectPreviousWeapon();

    void selectWeapon(unsigned idx);

private:
    float mX = 0, mY = 0, _speed = 0;
    float _angle = 0.0f;

    std::vector<Weapon> mWeapons;
    unsigned mSelectedWeaponIdx = 0;
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
