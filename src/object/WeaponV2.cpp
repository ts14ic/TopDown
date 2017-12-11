//
// Created by ts14ic on 12/11/17.
//

#include "WeaponV2.h"
#include "WeaponBuilder.h"
#include "Bullet.h"
#include "../assets/Assets.h"

WeaponV2::WeaponV2(const WeaponBuilder& builder)
        : mMaxAmmo{builder.getMaxAmmo()},
          mCurrentAmmo{builder.getMaxAmmo()},
          mProjectilesPerShot{builder.getProjectilesPerShot()},
          mLength{builder.getLength()},
          mDamage{builder.getProjectileDamage()},
          mProjectileSpeed{builder.getProjectileSpeed()},
          mSpread{builder.getProjectileSpread()},
          mFireSounds{builder.getFireSounds()},
          mFireCooldown(builder.getFireCooldown()),
          mReloadCooldown(builder.getReloadCooldown()) {
    mFireCooldownTimer.start();
}

void WeaponV2::startReloading() {
    mReloadCooldownTimer.start();
    mIsReloading = true;
}

void WeaponV2::playFireSound(Assets& assets) {
    if(!mFireSounds.empty()) {
        if(mCurrentFireSound >= mFireSounds.size()) {
            mCurrentFireSound = 0;
        }

        assets.sound(mFireSounds[mCurrentFireSound]).play();
        mCurrentFireSound++;
    }
}

void WeaponV2::spawnBullets(GameObject const& shooter) {
    for(int i = 0; i < mProjectilesPerShot; ++i) {
        Bullet b(shooter, *this);
        bullets().push_back(b);
    }
}

void WeaponV2::shoot(Assets& assets, GameObject const& shooter) {
    if(mFireCooldownTimer.passed(mFireCooldown) && mCurrentAmmo > 0) {
        spawnBullets(shooter);

        playFireSound(assets);

        --mCurrentAmmo;
        if(mCurrentAmmo < 1) {
            startReloading();
        }

        mFireCooldownTimer.start();
    }
}

int WeaponV2::length() const {
    return mLength;
}

int WeaponV2::dmg() const {
    return mDamage;
}

float WeaponV2::getProjectileSpeed() const {
    return mProjectileSpeed;
}

float WeaponV2::spread() const {
    return mSpread;
}

bool WeaponV2::reloading() const {
    return mIsReloading;
}

void WeaponV2::reload() {
    if(mIsReloading && mReloadCooldownTimer.passed(mReloadCooldown)) {
        mCurrentAmmo = mMaxAmmo;
        mIsReloading = false;
    }
    // todo add support for shotgun's interrupted reload
//    if(mIsReloading && mReloadCooldownTimer.passed(1000)) {
//        if(mCurrentAmmo == 0) {
//            mCurrentAmmo++;
//            mReloadCooldownTimer.start();
//        } else {
//            mCurrentAmmo++;
//            mIsReloading = false;
//        }
//    }
}
