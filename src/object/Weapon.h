//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../timer/StopWatch.h"
#include "../engine/AudioContext.h"
#include <vector>
#include <string>

class GameObject;

class Assets;

class WeaponBuilder;

class Random;

class Weapon {
public:
    explicit Weapon(const WeaponBuilder& builder);

    void pullTrigger(Random& random, Assets& assets, AudioContext& audioContext, GameObject const& shooter);

    void tryReload();

    bool isReloading() const;

    std::string getName() const;

    int getLength() const;

    int getProjectileDamage() const;

    float getProjectileSpeed() const;

    float getProjectileSpread() const;

private:
    void startReloading();

    void playFireSound(Assets& assets, AudioContext& audioContext);

    void spawnBullets(Random& random, GameObject const& shooter);

private:
    StopWatch mFireCooldownTimer;
    StopWatch mReloadCooldownTimer;
    bool mIsReloading = false;

    std::string mName;
    int mMaxAmmo;
    int mCurrentAmmo;
    int mProjectilesPerShot;
    int mWeaponLength;
    int mProjectileDamage;
    float mProjectileSpeed;
    float mProjectileSpread;
    // todo Move sound generation out of this class
    std::vector<std::string> mFireSounds;
    unsigned mCurrentFireSound = 0;
    unsigned mFireCooldown;
    unsigned mReloadCooldown;
};
