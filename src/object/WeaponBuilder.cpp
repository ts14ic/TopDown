//
// Created by ts14ic on 12/11/17.
//

#include "WeaponBuilder.h"
#include "Weapon.h"

WeaponBuilder& WeaponBuilder::maxAmmo(int maxAmmo) {
    mMaxAmmo = maxAmmo;
    return *this;
}

WeaponBuilder& WeaponBuilder::length(int length) {
    mLength = length;
    return *this;
}

WeaponBuilder& WeaponBuilder::fireCooldown(unsigned cooldown) {
    mFireCooldown = cooldown;
    return *this;
}

WeaponBuilder& WeaponBuilder::reloadCooldown(unsigned cooldown) {
    mReloadCooldown = cooldown;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectilesPerShot(int count) {
    mProjectilesPerShot = count;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectileDamage(int damage) {
    mProjectileDamage = damage;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectileSpeed(float speed) {
    mProjectileSpeed = speed;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectileSpread(float spread) {
    mProjectileSpread = spread;
    return *this;
}

WeaponBuilder& WeaponBuilder::fireSounds(const std::vector<std::string>& fireSounds) {
    mFireSounds = fireSounds;
    return *this;
}

Weapon WeaponBuilder::build() {
    return Weapon(*this);
}

int WeaponBuilder::getMaxAmmo() const {
    return mMaxAmmo;
}

int WeaponBuilder::getLength() const {
    return mLength;
}

unsigned int WeaponBuilder::getFireCooldown() const {
    return mFireCooldown;
}

unsigned int WeaponBuilder::getReloadCooldown() const {
    return mReloadCooldown;
}

int WeaponBuilder::getProjectilesPerShot() const {
    return mProjectilesPerShot;
}

int WeaponBuilder::getProjectileDamage() const {
    return mProjectileDamage;
}

float WeaponBuilder::getProjectileSpread() const {
    return mProjectileSpread;
}

float WeaponBuilder::getProjectileSpeed() const {
    return mProjectileSpeed;
}

const std::vector<std::string>& WeaponBuilder::getFireSounds() const {
    return mFireSounds;
}
