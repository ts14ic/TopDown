#include "StateMoon.h"
#include "math/maths.h"
#include "game/object/Zombie.h"
#include "game/object/Werewolf.h"
#include "game/object/Bullet.h"
#include "io/json/json.h"
#include "io/files/files.h"
#include "game/utils/Point2.h"
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

    _player.get_position() = make_point(_level_width / 2.0f, _level_height / 2.0f);

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
    if (event.get_type() == MousePointEvent::Type::Motion) {
        _mouse_pos.x = event.get_x();
        _mouse_pos.y = event.get_y();
    }

    _player.handle_mouse_event(event);
}

void StateMoon::handle_key_event(const KeyboardEvent& event) {
    _player.handle_key_event(event);
}

void StateMoon::restrict_pos(GameObject& o) {
    if (o.get_position().x < 0) o.get_position().x = 0;
    else if (o.get_position().x > _level_width) o.get_position().x = _level_width;

    if (o.get_position().y < 0) o.get_position().y = 0;
    else if (o.get_position().y > _level_height) o.get_position().y = _level_height;
}

void StateMoon::handle_logic() {
    if (_enemy_spawn_cooldown.ticks_passed_since_start(_game.get_engine().get_clock(), 50) &&
        (zombies().size() + werewolves().size() < 7)) {
        auto position = make_random_point();
        int type = _game.get_engine().get_random().get_int(0, 1);
        if (type == 0) {
            zombies().emplace_back(position.x, position.y);
        } else {
            werewolves().emplace_back(position.x, position.y);
        }

        _enemy_spawn_cooldown.restart(_game.get_engine().get_clock());
    }

    _player.handle_logic(_game.get_engine().get_random(), _game.get_engine(), _game.get_engine().get_audio());

    const auto& clock = _game.get_engine().get_clock();
    auto& random = _game.get_engine().get_random();

    int maxWidth = _level_width;
    int maxHeight = _level_height;
    // process bullet moving and collisions
    auto removeFrom = std::remove_if(bullets().begin(), bullets().end(),
                                     [maxWidth, maxHeight, &random, &clock](Bullet& b) {
                                         b.handle_logic();

                                         if ((b.get_position().x > maxWidth) || (b.get_position().x < 0) ||
                                             (b.get_position().y > maxHeight) || (b.get_position().y < 0)) {
                                             return true;
                                         }

                                         for (auto& z : zombies()) {
                                             if (objects_collide(b, z) && z.get_hp() > 0) {
                                                 z.damage(clock, b.get_damage());
                                                 return true;
                                             }
                                         }
                                         for (auto& w : werewolves()) {
                                             if (objects_collide(b, w) && w.get_hp() > 0) {
                                                 w.damage(clock, b.get_damage());
                                                 return true;
                                             }
                                             if (math::get_distance(b.get_position().x, b.get_position().y, w.get_position().x, w.get_position().y) < 50) {
                                                 w.teleport(clock, random);
                                             }
                                         }

                                         return false;
                                     });
    bullets().erase(removeFrom, bullets().end());

    zombies().erase(std::remove_if(zombies().begin(), zombies().end(), [this, &clock](Zombie& z) {
        z.set_target(_player.get_position());
        z.handle_logic();

        if (objects_collide(z, _player)) {
            _player.damage(clock, z.get_damage());
        }

        return z.is_dead();
    }), zombies().end());

    werewolves().erase(std::remove_if(werewolves().begin(), werewolves().end(), [this, &clock](Werewolf& w) {
        w.set_target(clock, _player.get_position());
        w.handle_logic(clock);

        if (objects_collide(w, _player)) {
            _player.damage(clock, w.get_damage());
        }

        return w.is_dead();
    }), werewolves().end());

    restrict_pos(_player);
    if (_player.is_dead()) _game.request_state_change(StateId::intro);
}

Point2<int> StateMoon::make_random_point() const {
    Random& random = _game.get_engine().get_random();
    if (random.get_int(0, 1) == 0) {
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

    graphic.render_texture(_background_tex, 0, 0);

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

    int x = _mouse_pos.x - texture.get_width() / 2;
    int y = _mouse_pos.y - texture.get_height() / 2;

    _crosshair_angle += 5.f * frames_count;
    if (_crosshair_angle > 360.f) {
        _crosshair_angle = 5.f;
    }

    graphic.render_texture(texture.get_name(), x, y, _crosshair_angle);
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
