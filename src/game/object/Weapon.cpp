#include "Weapon.h"

#include "Bullet.h"

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

void Weapon::start_reloading(const Clock& clock) {
    _reload_cooldown_timer.restart(clock);
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

void Weapon::spawn_bullets(Random& random, const GameObject& shooter, std::vector<Bullet>& bullets) {
    for (int i = 0; i < _projectiles_per_shot; ++i) {
        Bullet b(random, shooter, *this);
        bullets.push_back(b);
    }
}

void Weapon::pull_trigger(Engine& engine, const GameObject& shooter, std::vector<Bullet>& bullets) {
    const auto& clock = engine.get_clock();
    auto& random = engine.get_random();
    auto& audio = engine.get_audio();

    if (_fire_cooldown_timer.ticks_passed_since_start(clock, _fire_cooldown) && _current_ammo > 0) {
        spawn_bullets(random, shooter, bullets);

        play_fire_sound(audio);

        --_current_ammo;
        if (_current_ammo < 1) {
            start_reloading(clock);
        }

        _fire_cooldown_timer.restart(clock);
    }
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

void Weapon::try_reload(const Clock& clock) {
    if (_reloading && _reload_cooldown_timer.ticks_passed_since_start(clock, _reload_cooldown)) {
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
