//
// Created by ts14ic on 12/3/17.
//
#include "Uzi.h"
#include "../assets/Assets.h"
#include "Bullet.h"

Uzi::Uzi() {
    _cd.start();
}

int Uzi::dmg() const { return 10; }

float Uzi::speed() const { return 12.f; }

int Uzi::length() const { return 25; }

float Uzi::spread() const { return 5; }

bool Uzi::reloading() const { return _reloading; }

void Uzi::reload() {
    if(_reloading && _reload.passed(3000)) {
        _magAmmo = 25;
        _reloading = false;
    }
}

void Uzi::shoot(Assets& assets, GameObject const& sender) {
    static int sound = 1;

    if(_cd.passed(100) && _magAmmo > 0) {
        Bullet b(sender, *this);
        bullets().push_back(b);

        if(sound == 1) {
            assets.sound("uzi_shot1").play();
            sound = 2;
        } else {
            assets.sound("uzi_shot2").play();
            sound = 1;
        }

        --_magAmmo;
        if(_magAmmo < 1) {
            _reload.start();
            _reloading = true;
        }

        _cd.start();
    }
}
