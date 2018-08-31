//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../../engine/Timer.h"
#include "../../engine/AudioContext.h"
#include "../../engine/resources/Resources.h"
#include "../../engine/Random.h"
#include "../object/GameObject.h"
#include "../object/WeaponBuilder.h"
#include <vector>
#include <string>

class Weapon {
public:
    explicit Weapon(const WeaponBuilder& builder);

    void pullTrigger(Random& random, Resources& resources, AudioContext& audioContext, GameObject const& shooter);

    void tryReload(const Clock& clock);

    bool isReloading() const;

    std::string getName() const;

    int getLength() const;

    int getProjectileDamage() const;

    float getProjectileSpeed() const;

    float getProjectileSpread() const;

private:
    void startReloading(const Clock& clock);

    void playFireSound(Resources& resources, AudioContext& audioContext);

    void spawnBullets(Random& random, GameObject const& shooter);

private:
    Timer mFireCooldownTimer;
    Timer mReloadCooldownTimer;
    bool mIsReloading = false;

    std::string mName;
    int mMaxAmmo;
    int mCurrentAmmo;
    int mProjectilesPerShot;
    int mWeaponLength;
    int mProjectileDamage;
    float mProjectileSpeed;
    float mProjectileSpread;
    // TODO Move sound generation out of this class
    std::vector<std::string> mFireSounds;
    unsigned mCurrentFireSound = 0;
    unsigned mFireCooldown;
    unsigned mReloadCooldown;
};
