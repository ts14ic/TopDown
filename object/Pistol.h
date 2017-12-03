//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../StopWatch.h"
#include "GameObject.h"
#include "Weapon.h"

class Pistol : public Weapon {
public:
    Pistol();

    void shoot(GameObject const& shooter) override;

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
    int _magAmmo = 7;
};
