#include "StateMoon.h"
#include <game/object/Zombie.h>
#include <game/object/Werewolf.h>
#include <game/object/Bullet.h>
#include <engine/geometry/maths.h>
#include <engine/geometry/Point2.h>
#include <engine/log/Log.h>
#include <io/json/json.h>
#include <io/files/files.h>
#include <algorithm>

StateMoon::StateMoon(Game& game)
        : _game{game},
          _background_tex{"moon_background"},
          _level_width(game.get_engine().get_graphic().get_screen_width()),
          _level_height(game.get_engine().get_graphic().get_screen_height()),
          _enemy_spawn_cooldown{} {
    get_engine().get_graphic().load_texture(_background_tex, "assets/gfx/test_bg.png");

    _enemy_spawn_cooldown.restart();

    _player.set_position(_level_width / 2.0f, _level_height / 2.0f);

    parse_level_data();
}

void StateMoon::handle_window_event(const WindowEvent& event) {
}

void StateMoon::handle_mouse_event(const MouseScrollEvent& event) {
    _player.handle_mouse_event(event);
}

void StateMoon::handle_mouse_event(const MousePointEvent& event) {
    if (event.get_type() == MousePointEvent::Type::MOTION) {
        _mouse_pos = event.get_position();
    }

    _player.handle_mouse_event(event);
}

void StateMoon::handle_key_event(const KeyboardEvent& event) {
    _player.handle_key_event(event);
}

void StateMoon::restrict_pos(GameObject& object) {
    Transform transform = object.get_transform();

    if (transform.position.x < 0) {
        transform.position.x = 0;
    } else if (transform.position.x > _level_width) {
        transform.position.x = _level_width;
    }

    if (transform.position.y < 0) {
        transform.position.y = 0;
    } else if (transform.position.y > _level_height) {
        transform.position.y = _level_height;
    }

    object.set_transform(transform);
}

void StateMoon::handle_logic() {
    Random& random = get_engine().get_random();

    if (_enemy_spawn_cooldown.ticks_passed_since_start(50) &&
        (_zombies.size() + _werewolves.size() < 7)) {
        auto position = point_cast<float>(make_random_point());
        if (!random.get_bool()) {
            _zombies.emplace_back(position);
        } else {
            _werewolves.emplace_back(position);
        }

        _enemy_spawn_cooldown.restart();
    }

    handle_player_logic();
    handle_bullet_logic();
    handle_zombie_logic();
    handle_werewolf_logic();

    restrict_pos(_player);
    if (_player.is_dead()) _game.request_state_change(StateId::INTRO);
}

void StateMoon::handle_player_logic() {
    _player.handle_logic(get_engine(), _bullets);
}

void StateMoon::handle_bullet_logic() {
    auto& random = get_engine().get_random();

    auto remove_from = std::remove_if(_bullets.begin(), _bullets.end(), [&, this](Bullet& bullet) {
        Transform transform = bullet.get_transform();
        Speed speed = bullet.get_speed();
        auto bullet_damage = bullet.get_melee_damage();

        // TODO extract speed setting
        speed.current_speed = {
                math::cartesian_cos(transform.angle) * speed.max_speed,
                math::cartesian_sin(transform.angle) * speed.max_speed
        };
        transform.position = {
                transform.position.x + speed.current_speed.x,
                transform.position.y + speed.current_speed.y
        };

        if (position_out_of_level_area(transform.position)) {
            Log::d("bullet of level area, destroying");
            return true;
        }

        for (auto& zombie : _zombies) {
            if (circles_collide(transform.get_circle(), zombie.get_circle())
                && zombie.get_hp() > 0) {
                zombie.take_damage(bullet_damage);
                Log::d("zombie takes %d damage, bullet destroyed", bullet_damage);
                return true;
            }
        }
        for (auto& werewolf : _werewolves) {
            if (circles_collide(transform.get_circle(), werewolf.get_circle())
                && werewolf.has_hp() > 0) {
                werewolf.take_damage(bullet_damage);
                Log::d("werewolf takes %d damage, bullet destroyed", bullet_damage);
                return true;
            }
            if (math::get_distance(transform.position, werewolf.get_position()) < 50) {
                werewolf.teleport(random);
            }
        }

        bullet.set_current_speed(speed.current_speed);
        bullet.set_position(transform.position);
        return false;
    });
    _bullets.erase(remove_from, _bullets.end());
}

void StateMoon::handle_zombie_logic() {
    _zombies.erase(std::remove_if(_zombies.begin(), _zombies.end(), [&, this](Zombie& zombie) {
        zombie.set_target(_player.get_position());
        zombie.handle_logic();

        if (objects_collide(zombie, _player)) {
            _player.take_damage(zombie.get_melee_damage());
        }

        return zombie.is_dead();
    }), _zombies.end());
}

void StateMoon::handle_werewolf_logic() {
    _werewolves.erase(std::remove_if(_werewolves.begin(), _werewolves.end(), [&, this](Werewolf& werewolf) {
        werewolf.set_target(_player.get_position());
        werewolf.handle_logic();

        if (objects_collide(werewolf, _player)) {
            _player.take_damage(werewolf.get_melee_damage());
        }

        return werewolf.is_dead();
    }), _werewolves.end());
}

bool StateMoon::position_out_of_level_area(Point2<float> position) const {
    return (position.x > _level_width) || (position.x < 0) ||
           (position.y > _level_height) || (position.y < 0);
}

Point2<int> StateMoon::make_random_point() const {
    Random& random = get_engine().get_random();
    if (!random.get_bool()) {
        return make_point(
                random.get_int(0, _level_width),
                random.get_int(0, 1) * _level_height
        );
    } else {
        return make_point(
                random.get_int(0, 1) * _level_width,
                random.get_int(0, _level_height)
        );
    }
}

void StateMoon::handle_render(float milliseconds_passed, float milliseconds_per_frame) {
    float frames_passed = milliseconds_passed / milliseconds_per_frame;
    auto& engine = get_engine();
    auto& graphic = engine.get_graphic();
    graphic.clear_screen();

    auto& audio = engine.get_audio();
    audio.play_music("weather");

    graphic.render_texture(_background_tex, make_point(0, 0));

    _player.handle_render(graphic, frames_passed);

    for (auto& zombie : _zombies) {
        zombie.handle_render(engine, frames_passed);
    }

    for (auto& werewolf : _werewolves) {
        werewolf.handle_render(engine, graphic, audio, frames_passed);
    }

    for (auto& b : _bullets) {
        b.handle_render(graphic, frames_passed);
    }

    render_crosshair(frames_passed);

    graphic.refresh_screen();
}

void StateMoon::render_crosshair(float frames_count) {
    Graphic& graphic = get_engine().get_graphic();

    auto texture = graphic.get_texture(_player.is_reloading()
                                       ? "reload"
                                       : "crosshair");
    auto render_point = make_point(
            _mouse_pos.x - texture.get_size().get_width() / 2,
            _mouse_pos.y - texture.get_size().get_height() / 2
    );

    _crosshair_angle += 5.f * frames_count;
    if (_crosshair_angle > 360.f) {
        _crosshair_angle = 5.f;
    }

    graphic.render_texture(texture.get_name(), render_point, _crosshair_angle);
}

void StateMoon::parse_level_data() {
    using namespace json;

    auto document = parse_json(files::read_file_to_string("data/levels/moon.json"));

    for (const auto& weapon : get_array(document, "/player/weapons")) {

        auto builder = WeaponBuilder{get_czstring(weapon, "/name")}
                .fire_sounds(get_values<std::string>(weapon, "/fire_sounds"))
                .max_ammo(get_int(weapon, "/max_ammo"))
                .projectiles_per_shot(get_int(weapon, "/projectiles_per_shot"))
                .length(get_int(weapon, "/length"))
                .projectile_speed(get_int(weapon, "/projectile_speed"))
                .projectile_damage(get_int(weapon, "/projectile_damage"))
                .projectile_spread(get_int(weapon, "/projectile_spread"))
                .fire_cooldown(get_uint(weapon, "/fire_cooldown"))
                .reload_cooldown(get_uint(weapon, "/reload_cooldown"));

        _player.add_weapon(builder.build());
    }
}
