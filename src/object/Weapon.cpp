//
// Created by ts14ic on 12/11/17.
//
#include "Weapon.h"

#include "WeaponBuilder.h"
#include "Bullet.h"
#include "../assets/Assets.h"
#include "../assets/Sound.h"

Weapon::Weapon(const WeaponBuilder& builder)
        : mName{builder.getName()},
          mMaxAmmo{builder.getMaxAmmo()},
          mCurrentAmmo{builder.getMaxAmmo()},
          mProjectilesPerShot{builder.getProjectilesPerShot()},
          mWeaponLength{builder.getLength()},
          mProjectileDamage{builder.getProjectileDamage()},
          mProjectileSpeed{builder.getProjectileSpeed()},
          mProjectileSpread{builder.getProjectileSpread()},
          mFireSounds{builder.getFireSounds()},
          mFireCooldown(builder.getFireCooldown()),
          mReloadCooldown(builder.getReloadCooldown()) {
    mFireCooldownTimer.restart();
}

void Weapon::startReloading() {
    mReloadCooldownTimer.restart();
    mIsReloading = true;
}

void Weapon::playFireSound(Assets& assets, AudioContext& audioContext) {
    if(!mFireSounds.empty()) {
        if(mCurrentFireSound >= mFireSounds.size()) {
            mCurrentFireSound = 0;
        }

        audioContext.playSound(assets.getSound(mFireSounds[mCurrentFireSound]));
        mCurrentFireSound++;
    }
}

void Weapon::spawnBullets(Random& random, GameObject const& shooter) {
    for(int i = 0; i < mProjectilesPerShot; ++i) {
        Bullet b(random, shooter, *this);
        bullets().push_back(b);
    }
}

void Weapon::pullTrigger(Random& random, Assets& assets, AudioContext& audioContext, GameObject const& shooter) {
    if(mFireCooldownTimer.ticksHavePassed(mFireCooldown) && mCurrentAmmo > 0) {
        spawnBullets(random, shooter);

        playFireSound(assets, audioContext);

        --mCurrentAmmo;
        if(mCurrentAmmo < 1) {
            startReloading();
        }

        mFireCooldownTimer.restart();
    }
}

int Weapon::getLength() const {
    return mWeaponLength;
}

int Weapon::getProjectileDamage() const {
    return mProjectileDamage;
}

float Weapon::getProjectileSpeed() const {
    return mProjectileSpeed;
}

float Weapon::getProjectileSpread() const {
    return mProjectileSpread;
}

bool Weapon::isReloading() const {
    return mIsReloading;
}

void Weapon::tryReload() {
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

std::string Weapon::getName() const {
    return mName;
}
