#pragma once

#include <vector>
#include <string>

class Weapon; /* forward required for builder */

class WeaponBuilder {
public:
    explicit WeaponBuilder(std::string name);

    WeaponBuilder& max_ammo(int maxAmmo);

    WeaponBuilder& length(int length);

    WeaponBuilder& fire_cooldown(unsigned cooldown);

    WeaponBuilder& reload_cooldown(unsigned cooldown);

    WeaponBuilder& projectiles_per_shot(int count);

    WeaponBuilder& projectile_damage(int damage);

    WeaponBuilder& projectile_speed(float speed);

    WeaponBuilder& projectile_spread(float spread);

    WeaponBuilder& fire_sounds(const std::vector<std::string>& fireSounds);

    Weapon build();

    std::string get_name() const;

    int get_max_ammo() const;

    int get_length() const;

    unsigned int get_fire_cooldown() const;

    unsigned int get_reload_cooldown() const;

    int get_projectiles_per_shot() const;

    int get_projectile_damage() const;

    float get_projectile_spread() const;

    float get_projectile_speed() const;

    const std::vector<std::string>& get_fire_sounds() const;

private:
    std::string _name;
    int _max_ammo = 0;
    int _length = 0;
    unsigned _fire_cooldown = 0;
    unsigned _reload_cooldown = 0;
    int _projectiles_per_shot = 0;
    int _projectile_damage = 0;
    float _projectile_spread = 0.f;
    float _projectile_speed = 0.f;
    std::vector<std::string> _fire_sounds;
};
