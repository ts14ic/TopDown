//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "GameObject.h"
#include <vector>

class Weapon;

class Bullet : public GameObject {
public:
    Bullet(GameObject const& origin, Weapon const& weap);

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

    int dmg() const;

    void handle_logic();

    void handle_render(Assets& assets, RenderContext& renderContext);

private:
    int _dmg;
    float _x, _y, _angle, _speed;
};

std::vector<Bullet>& bullets();

