//
// Created by ts14ic on 12/3/17.
//
#include "Pistol.h"
#include "../assets/Assets.h"
#include "Bullet.h"

Pistol::Pistol() {
    _cd.start();
}

int Pistol::dmg() const { return 15; }

float Pistol::speed() const { return 12.f; }

int Pistol::length() const { return 10; }

float Pistol::spread() const { return 2; }

bool Pistol::reloading() const { return _reloading; }

void Pistol::reload() {
    if(_reloading && _reload.passed(1000)) {
        _magAmmo = 7;
        _reloading = false;
    }
}

void Pistol::shoot(Assets& assets, GameObject const& sender) {
    if(_cd.passed(350) && _magAmmo > 0) {
        Bullet b(sender, *this);
        bullets().push_back(b);

        assets.sound("pistol_shot").play();

        --_magAmmo;
        if(_magAmmo < 1) {
            _reload.start();
            _reloading = true;
        }

        _cd.start();
    }
}
