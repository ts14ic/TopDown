//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "Weapon.h"
#include "../timer/StopWatch.h"

class GameObject;

class Shotgun : public Weapon {
public:
    Shotgun();

    void shoot(Assets& assets, GameObject const& shooter) override;

    int dmg() const override;

    float speed() const override;

    int length() const override;

    float spread() const override;

    bool reloading() const override;

    void reload() override;

private:
    StopWatch _cd;
    StopWatch _reload;

    bool _reloading = false;
    int _magAmmo = 2;
};
