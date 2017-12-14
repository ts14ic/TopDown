//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "Damageable.h"
#include "../engine/Timer.h"
#include "../engine/AudioContext.h"
#include <vector>

class Random;

class Werewolf : public Damageable {
public:
    Werewolf(float x, float y);

    // GameObject legacy
    float getX() const override;

    float getY() const override;

    void setX(float x) override;

    void setY(float y) override;

    void setPos(float x, float y) override;

    float getAngle() const override;

    float getSpeed() const override;

    void setAngle(float a) override;

    void setSpeed(float s) override;

    Circle getCircle() const override;

    std::string getTexName() const override;

    // Damageable legacy
    int hp() const override;

    int defaultHp() const override;

    int dmg() const override;

    void damage(const Clock& clock, int d) override;

    bool dead() const override;

    // StateMoon interface
    void set_target(const Clock& clock, float x, float y, bool ignore);

    void teleport(const Clock& clock, Random& random);

    void handle_logic(const Clock& clock);

    void handle_render(Resources& resources, GraphicContext& graphicContext, AudioContext& audioContext);

private:
    float _x, _y, _speed = 2.5f;
    float _angle = 0.f;
    int _hp;

    int _frame = 0;
    Timer mAttackCooldown;
    Timer mTeleportCooldown;

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
