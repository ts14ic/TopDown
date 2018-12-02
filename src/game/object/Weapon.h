#pragma once

#include "WeaponBuilder.h"
#include <game/timer/Timer.h>
#include <engine/audio/Audio.h>
#include <engine/Engine.h>
#include <engine/random/Random.h>
#include <vector>
#include <string>

class Bullet;

class Weapon {
public:
    explicit Weapon(const WeaponBuilder& builder);

    int pull_trigger(Audio& audio);

    void try_reload();

    bool is_reloading() const;

    std::string get_name() const;

    int get_length() const;

    int get_projectile_damage() const;

    float get_projectile_speed() const;

    float get_projectile_spread() const;

private:
    void start_reloading();

    void play_fire_sound(Audio& audio);

private:
    Timer _fire_cooldown_timer;
    Timer _reload_cooldown_timer;
    bool _reloading = false;

    std::string _name;
    int _max_ammo;
    int _current_ammo;
    int _projectiles_per_shot;
    int _weapon_length;
    int _projectile_damage;
    float _projectile_speed;
    float _projectile_spread;
    // TODO Move sound generation out of this class
    std::vector<std::string> _fire_sounds;
    unsigned _current_fire_sound = 0;
    unsigned _fire_cooldown;
    unsigned _reload_cooldown;
};
