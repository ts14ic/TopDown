//
// Created by ts14ic on 12/11/17.
//

#pragma once

#include <vector>
#include <string>

class WeaponV2;

class WeaponBuilder {
public:
    WeaponBuilder& maxAmmo(int maxAmmo);

    WeaponBuilder& length(int length);

    WeaponBuilder& fireCooldown(unsigned cooldown);

    WeaponBuilder& reloadCooldown(unsigned cooldown);

    WeaponBuilder& projectilesPerShot(int count);

    WeaponBuilder& projectileDamage(int damage);

    WeaponBuilder& projectileSpeed(float speed);

    WeaponBuilder& projectileSpread(float spread);

    WeaponBuilder& fireSounds(const std::vector<std::string>& fireSounds);

    WeaponV2 build();

    int getMaxAmmo() const;

    int getLength() const;

    unsigned int getFireCooldown() const;

    unsigned int getReloadCooldown() const;

    int getProjectilesPerShot() const;

    int getProjectileDamage() const;

    float getProjectileSpread() const;

    float getProjectileSpeed() const;

    const std::vector<std::string>& getFireSounds() const;

private:
    int mMaxAmmo = 0;
    int mLength = 0;
    unsigned mFireCooldown = 0;
    unsigned mReloadCooldown = 0;
    int mProjectilesPerShot = 0;
    int mProjectileDamage = 0;
    float mProjectileSpread = 0.f;
    float mProjectileSpeed = 0.f;
    std::vector<std::string> mFireSounds;
};

