//
// Created by ts14ic on 12/11/17.
//

#pragma once

#include "Weapon.h"
#include "../timer/StopWatch.h"
#include <vector>
#include <string>

// todo add a WeaponBuilder
// todo add a WeaponFactory

class WeaponV2 : public Weapon {
public:
    WeaponV2(int maxAmmo, int projectilesPerShot, int length, int damage, float projectileSpeed, int mFireCooldown,
             int mReloadCooldown, float spread, std::vector<std::string> fireSounds);

    void shoot(Assets& assets, GameObject const& shooter) override;

    int length() const override;

    int dmg() const override;

    float getProjectileSpeed() const override;

    float spread() const override;

    bool reloading() const override;

    void reload() override;

private:
    void startReloading();

    void playFireSound(Assets& assets);

    void spawnBullets(const GameObject& shooter);

private:
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
