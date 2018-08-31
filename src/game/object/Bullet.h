//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include "../../engine/Random.h"
#include <vector>

class Bullet : public GameObject {
public:
    Bullet(Random& random, GameObject const& origin, Weapon const& weap);

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

    int dmg() const;

    void handle_logic();

    void handleRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio);

private:
    int mDamage;
    float mX;
    float mY;
    float mAngle;
    float mMaxSpeed;
    float mCurrentSpeedX;
    float mCurrentSpeedY;
};

std::vector<Bullet>& bullets();

