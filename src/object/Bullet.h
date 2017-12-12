//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "GameObject.h"
#include "../engine/Random.h"
#include <vector>

class Weapon;

class Bullet : public GameObject {
public:
    Bullet(Random& random, GameObject const& origin, Weapon const& weap);

    float getX() const override;

    float getY() const override;

    float getAngle() const override;

    float getSpeed() const override;

    void setX(float x) override;

    void setY(float y) override;

    void setPos(float x, float y) override;

    void setAngle(float a) override;

    void setSpeed(float s) override;

    Circle getCircle() const override;

    std::string getTexName() const override;

    int dmg() const;

    void handle_logic();

    void handle_render(Assets& assets, RenderContext& renderContext);

private:
    int _dmg;
    float _x, _y, _angle, _speed;
};

std::vector<Bullet>& bullets();

