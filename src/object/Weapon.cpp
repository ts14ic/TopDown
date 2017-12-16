//
// Created by ts14ic on 12/11/17.
//
#include "Weapon.h"

#include "WeaponBuilder.h"
#include "Bullet.h"
#include "../resources/Resources.h"
#include "../resources/Sound.h"

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
//    mFireCooldownTimer.restart();
}

void Weapon::startReloading(const Clock& clock) {
    mReloadCooldownTimer.restart(clock);
    mIsReloading = true;
}

void Weapon::playFireSound(Resources& resources, AudioContext& audioContext) {
    if(!mFireSounds.empty()) {
        if(mCurrentFireSound >= mFireSounds.size()) {
            mCurrentFireSound = 0;
        }

        audioContext.playSound(resources.getSound(mFireSounds[mCurrentFireSound]));
        mCurrentFireSound++;
    }
}

void Weapon::spawnBullets(Random& random, GameObject const& shooter) {
    for(int i = 0; i < mProjectilesPerShot; ++i) {
        Bullet b(random, shooter, *this);
        bullets().push_back(b);
    }
}

void Weapon::pullTrigger(Random& random, Resources& resources, AudioContext& audioContext, GameObject const& shooter) {
    const auto& clock = resources.getClock();
    if(mFireCooldownTimer.haveTicksPassedSinceStart(clock, mFireCooldown) && mCurrentAmmo > 0) {
        spawnBullets(random, shooter);

        playFireSound(resources, audioContext);

        --mCurrentAmmo;
        if(mCurrentAmmo < 1) {
            startReloading(clock);
        }

        mFireCooldownTimer.restart(clock);
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

void Weapon::tryReload(const Clock& clock) {
    if(mIsReloading && mReloadCooldownTimer.haveTicksPassedSinceStart(clock, mReloadCooldown)) {
        mCurrentAmmo = mMaxAmmo;
        mIsReloading = false;
    }
    // TODO add support for shotgun's interrupted reload
    // TODO add support semi-automatic fire
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
