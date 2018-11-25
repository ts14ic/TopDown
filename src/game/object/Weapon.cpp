#include "Weapon.h"
#include <engine/log/Log.h>

Weapon::Weapon(const WeaponBuilder& builder)
        : _name{builder.get_name()},
          _max_ammo{builder.get_max_ammo()},
          _current_ammo{builder.get_max_ammo()},
          _projectiles_per_shot{builder.get_projectiles_per_shot()},
          _weapon_length{builder.get_length()},
          _projectile_damage{builder.get_projectile_damage()},
          _projectile_speed{builder.get_projectile_speed()},
          _projectile_spread{builder.get_projectile_spread()},
          _fire_sounds{builder.get_fire_sounds()},
          _fire_cooldown(builder.get_fire_cooldown()),
          _reload_cooldown(builder.get_reload_cooldown()) {
//    _fire_cooldown_timer.restart();
}

void Weapon::start_reloading() {
    _reload_cooldown_timer.restart();
    _reloading = true;
}

void Weapon::play_fire_sound(Audio& audio) {
    if (!_fire_sounds.empty()) {
        if (_current_fire_sound >= _fire_sounds.size()) {
            _current_fire_sound = 0;
        }

        audio.play_sound(_fire_sounds[_current_fire_sound]);
        _current_fire_sound++;
    }
}

int Weapon::pull_trigger(Engine& engine) {
    auto projectiles_shot = 0;
    if (_fire_cooldown_timer.ticks_passed_since_start(_fire_cooldown) && _current_ammo > 0) {
        projectiles_shot = _projectiles_per_shot;

        play_fire_sound(engine.get_audio());

        --_current_ammo;
        Log::d("shot from %s, ammo [%d/%d]", _name.c_str(), _current_ammo, _max_ammo);
        if (_current_ammo < 1) {
            start_reloading();
        }

        _fire_cooldown_timer.restart();
    }
    return projectiles_shot;
}

int Weapon::get_length() const {
    return _weapon_length;
}

int Weapon::get_projectile_damage() const {
    return _projectile_damage;
}

float Weapon::get_projectile_speed() const {
    return _projectile_speed;
}

float Weapon::get_projectile_spread() const {
    return _projectile_spread;
}

bool Weapon::is_reloading() const {
    return _reloading;
}

void Weapon::try_reload() {
    if (_reloading && _reload_cooldown_timer.ticks_passed_since_start(_reload_cooldown)) {
        _current_ammo = _max_ammo;
        _reloading = false;
    }
    // TODO add support for shotgun's interrupted reload
    // TODO add support semi-automatic fire
//    if(_reloading && _reload_cooldown_timer.ticksHavePassed(1000)) {
//        if(_current_ammo == 0) {
//            _current_ammo++;
//            _reload_cooldown_timer.restart();
//        } else {
//            _current_ammo++;
//            _reloading = false;
//        }
//    }
}

std::string Weapon::get_name() const {
    return _name;
}
