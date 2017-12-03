//
// Created by ts14ic on 12/3/17.
//
#include "Shotgun.h"
#include "../sound/Sound.h"
#include "Bullet.h"

Shotgun::Shotgun() {
    _cd.start();
}

int Shotgun::dmg() const { return 7; }

float Shotgun::speed() const { return 8.f; }

int Shotgun::length() const { return 45; }

float Shotgun::spread() const { return 20; }

bool Shotgun::reloading() const { return _reloading; }

void Shotgun::reload() {
    if(_reloading && _reload.passed(1000)) {
        if(_magAmmo == 0) {
            _magAmmo++;
            _reload.start();
        } else {
            _magAmmo++;
            _reloading = false;
        }
    }
}

void Shotgun::shoot(GameObject const& sender) {
    if(_cd.passed(200) && _magAmmo > 0) {
        for(int i = 0; i < 8; ++i) {
            Bullet b(sender, *this);
            bullets().push_back(b);
        }
        sounds("shotgun_shot").play();

        --_magAmmo;
        if(_magAmmo < 1) {
            _reload.start();
            _reloading = true;
        }

        _cd.start();
    }
}
