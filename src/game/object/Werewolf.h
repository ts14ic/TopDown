//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "Damageable.h"
#include "engine/Timer.h"
#include "engine/Random.h"
#include "engine/AudioContext.h"
#include <vector>

class Werewolf : public Damageable {
public:
    Werewolf(float x, float y);

    // GameObject legacy
    float getX() const override;

    float getY() const override;

    float getAngle() const override;

    float getMaxMovementSpeed() const override;

    float getCurrentSpeedX() const override;

    float getCurrentSpeedY() const override;

    void setX(float x) override;

    void setY(float y) override;

    void setPos(float x, float y) override;

    void setAngle(float a) override;

    void setMaxMovementSpeed(float s) override;

    void setCurrentSpeedX(float speedX) override;

    void setCurrentSpeedY(float speedY) override;

    void setCurrentSpeed(float speedX, float speedY) override;

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

    void handleLogic(const Clock& clock);

    void handleRender(Resources& resources, GraphicContext& graphicContext, AudioContext& audioContext,
                      float predictionRatio);

private:
    float mX = 0.f;
    float mY = 0.f;
    float mCurrentSpeedX = 0.f;
    float mCurrentSpeedY = 0.f;
    float mMaxMovementSpeed = 2.5f;
    float mViewAngle = 0.f;

    int mCurrentHp;

    int mAnimationFrame = 0;
    Timer mAttackCooldown;
    Timer mTeleportCooldown;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        TELEPORTING = 0x4,
        DYING = 0x8
    };
    int mAiState = IDLE;
};

std::vector<Werewolf>& werewolves();
