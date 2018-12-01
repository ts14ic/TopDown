#include "WeaponBuilder.h"
#include "Weapon.h"

WeaponBuilder::WeaponBuilder(std::string name)
        : _name{std::move(name)} {}

WeaponBuilder& WeaponBuilder::max_ammo(int maxAmmo) {
    _max_ammo = maxAmmo;
    return *this;
}

WeaponBuilder& WeaponBuilder::length(int length) {
    _length = length;
    return *this;
}

WeaponBuilder& WeaponBuilder::fire_cooldown(unsigned cooldown) {
    _fire_cooldown = cooldown;
    return *this;
}

WeaponBuilder& WeaponBuilder::reload_cooldown(unsigned cooldown) {
    _reload_cooldown = cooldown;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectiles_per_shot(int count) {
    _projectiles_per_shot = count;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectile_damage(int damage) {
    _projectile_damage = damage;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectile_speed(float speed) {
    _projectile_speed = speed;
    return *this;
}

WeaponBuilder& WeaponBuilder::projectile_spread(float spread) {
    _projectile_spread = spread;
    return *this;
}

WeaponBuilder& WeaponBuilder::fire_sounds(const std::vector<std::string>& fireSounds) {
    _fire_sounds = fireSounds;
    return *this;
}

Weapon WeaponBuilder::build() {
    return Weapon(*this);
}

std::string WeaponBuilder::get_name() const {
    return _name;
}

int WeaponBuilder::get_max_ammo() const {
    return _max_ammo;
}

int WeaponBuilder::get_length() const {
    return _length;
}

unsigned int WeaponBuilder::get_fire_cooldown() const {
    return _fire_cooldown;
}

unsigned int WeaponBuilder::get_reload_cooldown() const {
    return _reload_cooldown;
}

int WeaponBuilder::get_projectiles_per_shot() const {
    return _projectiles_per_shot;
}

int WeaponBuilder::get_projectile_damage() const {
    return _projectile_damage;
}

float WeaponBuilder::get_projectile_spread() const {
    return _projectile_spread;
}

float WeaponBuilder::get_projectile_speed() const {
    return _projectile_speed;
}

const std::vector<std::string>& WeaponBuilder::get_fire_sounds() const {
    return _fire_sounds;
}
