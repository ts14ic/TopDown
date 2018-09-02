#include "StateMoon.h"
#include <game/object/Zombie.h>
#include <game/object/Werewolf.h>
#include <game/object/Bullet.h>
#include <engine/geometry/maths.h>
#include <engine/geometry/Point2.h>
#include <io/json/json.h>
#include <io/files/files.h>
#include <algorithm>

StateMoon::StateMoon(Game& game)
        : _game{game},
          _background_tex{"moon_background"},
          _level_width(game.get_engine().get_graphic().get_screen_width()),
          _level_height(game.get_engine().get_graphic().get_screen_height()),
          _enemy_spawn_cooldown{} {
    _game.get_engine().get_graphic().load_texture(_background_tex, "assets/gfx/test_bg.png");

    zombies().clear();
    werewolves().clear();
    _enemy_spawn_cooldown.restart(game.get_engine().get_clock());

    _player.set_position(_level_width / 2.0f, _level_height / 2.0f);

    parse_level_data();
}

StateMoon::StateMoon(const StateMoon& other)
        : StateMoon{other._game} {
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
    if (object.get_position().x < 0) {
        object.set_x(0);
    } else if (object.get_position().x > _level_width) {
        object.set_x(_level_width);
    }

    if (object.get_position().y < 0) {
        object.set_y(0);
    }
    else if (object.get_position().y > _level_height) {
        object.set_y(_level_height);
    }
}

void StateMoon::handle_logic() {
    Random& random = _game.get_engine().get_random();
    const Clock& clock = _game.get_engine().get_clock();

    if (_enemy_spawn_cooldown.ticks_passed_since_start(clock, 50) &&
        (zombies().size() + werewolves().size() < 7)) {
        auto position = point_cast<float>(make_random_point());
        if (!random.get_bool()) {
            zombies().emplace_back(position);
        } else {
            werewolves().emplace_back(position);
        }

        _enemy_spawn_cooldown.restart(clock);
    }

    _player.handle_logic(random, _game.get_engine(), _game.get_engine().get_audio());

    // process bullet moving and collisions
    auto remove_from = std::remove_if(bullets().begin(), bullets().end(), [&, this](Bullet& bullet) {
        bullet.handle_logic();

        if (position_out_of_level_area(bullet.get_position())) {
            return true;
        }

        for (auto& zombie : zombies()) {
            if (objects_collide(bullet, zombie) && zombie.has_hp()) {
                zombie.damage(clock, bullet.get_damage());
                return true;
            }
        }
        for (auto& werewolf : werewolves()) {
            if (objects_collide(bullet, werewolf) && werewolf.has_hp()) {
                werewolf.damage(clock, bullet.get_damage());
                return true;
            }
            if (math::get_distance(bullet.get_position(), werewolf.get_position()) < 50) {
                werewolf.teleport(clock, random);
            }
        }

        return false;
    });
    bullets().erase(remove_from, bullets().end());

    zombies().erase(std::remove_if(zombies().begin(), zombies().end(), [&, this](Zombie& z) {
        z.set_target(_player.get_position());
        z.handle_logic();

        if (objects_collide(z, _player)) {
            _player.damage(clock, z.get_damage());
        }

        return z.is_dead();
    }), zombies().end());

    werewolves().erase(std::remove_if(werewolves().begin(), werewolves().end(), [&, this](Werewolf& w) {
        w.set_target(clock, _player.get_position());
        w.handle_logic(clock);

        if (objects_collide(w, _player)) {
            _player.damage(clock, w.get_damage());
        }

        return w.is_dead();
    }), werewolves().end());

    restrict_pos(_player);
    if (_player.is_dead()) _game.request_state_change(StateId::INTRO);
}

bool StateMoon::position_out_of_level_area(Point2<float> position) const {
    return (position.x > _level_width) || (position.x < 0) ||
           (position.y > _level_height) || (position.y < 0);
}

Point2<int> StateMoon::make_random_point() const {
    Random& random = _game.get_engine().get_random();
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

void StateMoon::handle_render(float frames_count) {
    auto& engine = _game.get_engine();
    auto& graphic = engine.get_graphic();
    graphic.clear_screen();

    auto& audio = engine.get_audio();
    audio.play_music("weather");

    graphic.render_texture(_background_tex, make_point(0, 0));

    _player.handle_render(engine, graphic, frames_count);

    for (auto& z : zombies()) {
        z.handle_render(engine, graphic, audio, frames_count);
    }

    for (auto& w : werewolves()) {
        w.handle_render(engine, graphic, audio, frames_count);
    }

    for (auto& b : bullets()) {
        b.handle_render(engine, graphic, frames_count);
    }

    render_crosshair(frames_count);

    graphic.refresh_screen();
}

void StateMoon::render_crosshair(float frames_count) {
    Graphic& graphic = _game.get_engine().get_graphic();

    auto texture = graphic.get_texture(_player.reloading()
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

        _player.addWeapon(builder.build());
    }
}
