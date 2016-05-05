#include "GameObject.h"
#include "Sound.h"

/* ================= Pistol ================= */
Pistol::Pistol() {
    _cd.start();
}

int   Pistol::dmg()    const { return 15; }
float Pistol::speed()  const { return 12.f; }
int   Pistol::length() const { return 10; }
float Pistol::spread() const { return 2; }
bool  Pistol::reloading() const { return _reloading; }

void Pistol::reload() {
    if(_reloading && _reload.passed(1000)) {
        _magAmmo = 7;
        _reloading = false;
    }
}

void Pistol::shoot(Object const& sender) {
    if(_cd.passed(350) && _magAmmo > 0) {
        Bullet b(sender, *this);
        bullets().push_back(b);
        
        sounds("pistol_shot").play();
        
        -- _magAmmo;
        if(_magAmmo < 1) {
            _reload.start();
            _reloading = true;
        }
        
        _cd.start();
    }
}

/* ================= Shotgun ======================= */
Shotgun::Shotgun() {
    _cd.start();
}

int   Shotgun::dmg()    const { return 7; }
float Shotgun::speed()  const { return 8.f; }
int   Shotgun::length() const { return 45; }
float Shotgun::spread() const { return 20; }
bool  Shotgun::reloading() const { return _reloading; }

void Shotgun::reload() {
    if(_reloading && _reload.passed(1000)) {
        if(_magAmmo == 0) {
            _magAmmo++;
            _reload.start();
        }
        else {
            _magAmmo++;
            _reloading = false;
        }
    }
}

void Shotgun::shoot(Object const& sender) {
    if(_cd.passed(200) && _magAmmo > 0) {
        for(int i = 0; i < 8; ++i) {
            Bullet b(sender, *this);
            bullets().push_back(b);
        }
        sounds("shotgun_shot").play();
        
        -- _magAmmo;
        if(_magAmmo < 1) {
            _reload.start();
            _reloading = true;
        }
        
        _cd.start();
    }
}
