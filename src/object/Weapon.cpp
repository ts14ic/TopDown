//
// Created by ts14ic on 12/11/17.
//
#include "Weapon.h"

#include "WeaponBuilder.h"
#include "Bullet.h"
#include "../assets/Assets.h"

Weapon::Weapon(const WeaponBuilder& builder)
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
    mFireCooldownTimer.restart();
}

void Weapon::startReloading() {
    mReloadCooldownTimer.restart();
    mIsReloading = true;
}

void Weapon::playFireSound(Assets& assets) {
    if(!mFireSounds.empty()) {
        if(mCurrentFireSound >= mFireSounds.size()) {
            mCurrentFireSound = 0;
        }

        assets.sound(mFireSounds[mCurrentFireSound]).play();
        mCurrentFireSound++;
    }
}

void Weapon::spawnBullets(GameObject const& shooter) {
    for(int i = 0; i < mProjectilesPerShot; ++i) {
        Bullet b(shooter, *this);
        bullets().push_back(b);
    }
}

void Weapon::shoot(Assets& assets, GameObject const& shooter) {
    if(mFireCooldownTimer.ticksHavePassed(mFireCooldown) && mCurrentAmmo > 0) {
        spawnBullets(shooter);

        playFireSound(assets);

        --mCurrentAmmo;
        if(mCurrentAmmo < 1) {
            startReloading();
        }

        mFireCooldownTimer.restart();
    }
}

int Weapon::length() const {
    return mLength;
}

int Weapon::dmg() const {
    return mDamage;
}

float Weapon::getProjectileSpeed() const {
    return mProjectileSpeed;
}

float Weapon::spread() const {
    return mSpread;
}

bool Weapon::reloading() const {
    return mIsReloading;
}

void Weapon::reload() {
    if(mIsReloading && mReloadCooldownTimer.ticksHavePassed(mReloadCooldown)) {
        mCurrentAmmo = mMaxAmmo;
        mIsReloading = false;
    }
    // todo add support for shotgun's interrupted reload
//    if(mIsReloading && mReloadCooldownTimer.ticksHavePassed(1000)) {
//        if(mCurrentAmmo == 0) {
//            mCurrentAmmo++;
//            mReloadCooldownTimer.restart();
//        } else {
//            mCurrentAmmo++;
//            mIsReloading = false;
//        }
//    }
}
