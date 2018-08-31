#pragma once

#include "Damageable.h"
#include "engine/Timer.h"
#include "engine/AudioContext.h"
#include "engine/graphic/GraphicContext.h"
#include <vector>

class Zombie : public Damageable {
public:
    Zombie(int x, int y);

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

    void setAngle(float angle) override;

    void setMaxMovementSpeed(float speed) override;

    void setCurrentSpeedX(float speedX) override;

    void setCurrentSpeedY(float speedY) override;

    void setCurrentSpeed(float speedX, float speedY) override;

    Circle getCircle() const override;

    std::string getTexName() const override;

    // Damageable legacy
    int hp() const override;

    int defaultHp() const override;

    bool dead() const override;

    int dmg() const override;

    void damage(const Clock& clock, int d) override;

    // StateMoon interface
    void set_target(float x, float y, bool ignore = false);

    void handle_logic();

    void handleRender(Resources& resources, GraphicContext& graphicContext, AudioContext& audioContext,
                      float predictionRatio);

private:
    float mX = 0.f;
    float mY = 0.f;
    float mCurrentSpeedX = 0.f;
    float mCurrentSpeedY = 0.f;
    float mAngle = 0.f;
    float mSpeed = 1.7f;

    int mCurrentHp = 0;
    int mAnimationFrame = 0;

    Timer mTimer;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        DYING = 0x4
    };
    int mAiState = IDLE;
};

std::vector<Zombie>& zombies();
