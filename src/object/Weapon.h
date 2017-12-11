//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../timer/StopWatch.h"
#include <vector>
#include <string>

class GameObject;
class Assets;
class WeaponBuilder;

class Weapon {
public:
    explicit Weapon(const WeaponBuilder& builder);

    void shoot(Assets& assets, GameObject const& shooter);

    int length() const;

    int dmg() const;

    float getProjectileSpeed() const;

    std::string getName() const;

    float spread() const;

    bool reloading() const;

    void reload();

private:

    void startReloading();

    void playFireSound(Assets& assets);

    void spawnBullets(const GameObject& shooter);

private:
    std::string mName;

    // todo Move sound generation out of this class
    std::vector<std::string> mFireSounds;
    int mCurrentFireSound = 0;

    StopWatch mFireCooldownTimer;
    StopWatch mReloadCooldownTimer;

    int mCurrentAmmo;
    int mMaxAmmo;
    int mProjectilesPerShot;
    int mLength;
    int mDamage;
    float mProjectileSpeed;
    unsigned int mFireCooldown;
    unsigned int mReloadCooldown;
    float mSpread;
    bool mIsReloading;
};
