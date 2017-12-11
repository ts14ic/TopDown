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

    void pullTrigger(Assets& assets, GameObject const& shooter);

    void tryReload();

    bool isReloading() const;

    std::string getName() const;

    int getLength() const;

    int getProjectileDamage() const;

    float getProjectileSpeed() const;

    float getProjectileSpread() const;

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
    int mWeaponLength;
    int mProjectileDamage;
    float mProjectileSpeed;
    unsigned int mFireCooldown;
    unsigned int mReloadCooldown;
    float mProjectileSpread;
    bool mIsReloading;
};
