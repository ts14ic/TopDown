//
// Created by ts14ic on 12/3/17.
//
#pragma once

class GameObject;
class Assets;

enum EWeapon {
    WEAPON_PISTOL,
    WEAPON_FIRST = WEAPON_PISTOL,
    WEAPON_SHOTGUN,
    WEAPON_UZI,
    WEAPON_LAST = WEAPON_UZI,
    WEAPON_TOTAL
};

class Weapon {
public:
    virtual void shoot(Assets& assets, GameObject const& shooter) = 0;

    virtual int length() const = 0;

    virtual int dmg() const = 0;

    virtual float speed() const = 0;

    virtual float spread() const = 0;

    virtual bool reloading() const = 0;

    virtual void reload() = 0;

    virtual ~Weapon() = 0;
};
