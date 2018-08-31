#include "StateMoon.h"
#include "math/maths.h"
#include "game/object/Zombie.h"
#include "game/object/Werewolf.h"
#include "game/object/Bullet.h"
#include <algorithm>

StateMoon::StateMoon(Game& engine)
        : _engine{engine},
          _background_tex{"moon_background"},
          _level_width(engine.get_graphic_context().get_screen_width()),
          _level_height(engine.get_graphic_context().get_screen_height()),
          _enemy_spawn_cooldown{} {
    engine.get_resources().load_texture(_background_tex, "assets/gfx/test_bg.png");

    zombies().clear();
    werewolves().clear();
    _enemy_spawn_cooldown.restart(engine.get_clock());

    _player.set_position(_level_width / 2.0f, _level_height / 2.0f);

    parse_level_data();
}

StateMoon::StateMoon(const StateMoon& other)
        : StateMoon{other._engine} {
}

void StateMoon::handle_window_event(const WindowEvent &event) {
}

void StateMoon::handle_mouse_event(const MouseEvent &event) {
    if(event.get_type() == MouseEvent::Type::Motion) {
        _mouse_x = static_cast<int>(event.get_x());
        _mouse_y = static_cast<int>(event.get_y());
    }

    _player.handle_mouse_event(event);
}

void StateMoon::handle_key_event(const KeyboardEvent &event) {
    _player.handle_key_event(event);
}

void StateMoon::restrict_pos(GameObject& o) {
    if(o.get_x() < 0) o.set_x(0);
    else if(o.get_x() > _level_width) o.set_x(_level_width);

    if(o.get_y() < 0) o.set_y(0);
    else if(o.get_y() > _level_height) o.set_y(_level_height);
}

std::pair<int, int> randomPosition(Random& random, int width, int height) {
    int border = random.get_int(0, 1);
    int lx;
    int ly;
    if(border == 0) {
        lx = random.get_int(0, width);
        ly = random.get_int(0, 1) * height;
    } else {
        lx = random.get_int(0, 1) * width;
        ly = random.get_int(0, height);
    }
    return {lx, ly};
}

void StateMoon::handle_logic() {
    if(_enemy_spawn_cooldown.have_ticks_passed_since_start(_engine.get_clock(), 50) &&
       (zombies().size() + werewolves().size() < 7)) {
        auto position = randomPosition(_engine.get_random(), _level_width, _level_height);
        int type = _engine.get_random().get_int(0, 1);
        if(type == 0) {
            zombies().emplace_back(position.first, position.second);
        } else {
            werewolves().emplace_back(position.first, position.second);
        }

        _enemy_spawn_cooldown.restart(_engine.get_clock());
    }

    _player.handle_logic(_engine.get_random(), _engine.get_resources(), _engine.get_audio_context());

    const auto& clock = _engine.get_clock();
    auto& random = _engine.get_random();

    int maxWidth = _level_width;
    int maxHeight = _level_height;
    // process bullet moving and collisions
    auto removeFrom = std::remove_if(bullets().begin(), bullets().end(),
                                     [maxWidth, maxHeight, &random, &clock](Bullet& b) {
                                         b.handle_logic();

                                         if((b.get_x() > maxWidth) || (b.get_x() < 0) ||
                                            (b.get_y() > maxHeight) || (b.get_y() < 0)) {
                                             return true;
                                         }

                                         for(auto& z : zombies()) {
                                             if(objects_collide(b, z) && z.get_hp() > 0) {
                                                 z.damage(clock, b.get_damage());
                                                 return true;
                                             }
                                         }
                                         for(auto& w : werewolves()) {
                                             if(objects_collide(b, w) && w.get_hp() > 0) {
                                                 w.damage(clock, b.get_damage());
                                                 return true;
                                             }
                                             if(math::get_distance(b.get_x(), b.get_y(), w.get_x(), w.get_y()) < 50) {
                                                 w.teleport(clock, random);
                                             }
                                         }

                                         return false;
                                     });
    bullets().erase(removeFrom, bullets().end());

    zombies().erase(std::remove_if(zombies().begin(), zombies().end(), [this, &clock](Zombie& z) {
        z.set_target(_player.get_x(), _player.get_y());
        z.handle_logic();

        if(objects_collide(z, _player)) {
            _player.damage(clock, z.get_damage());
        }

        return z.is_dead();
    }), zombies().end());

    werewolves().erase(std::remove_if(werewolves().begin(), werewolves().end(), [this, &clock](Werewolf& w) {
        w.set_target(clock, _player.get_x(), _player.get_y(), false);
        w.handle_logic(clock);

        if(objects_collide(w, _player)) {
            _player.damage(clock, w.get_damage());
        }

        return w.is_dead();
    }), werewolves().end());

    restrict_pos(_player);
    if(_player.is_dead()) _engine.request_state_change(StateId::intro);
}

void render_crosshair(int mouseX, int mouseY, Resources &resources, GraphicContext &graphic_context, Player const &player,
                      float predictionRatio) {
    int x = mouseX - resources.get_texture("crosshair").get_width() / 2;
    int y = mouseY - resources.get_texture("crosshair").get_height() / 2;

    static float angle = 0.f;
    angle += 5.f * predictionRatio;
    if(angle > 360.f) angle = 5.f;

    graphic_context.render(resources.get_texture(player.reloading() ? "reload" : "crosshair"), x, y, angle);
}

void StateMoon::handle_render(float predictionRatio) {
    auto& render = _engine.get_graphic_context();
    render.clear_screen();

    auto& resources = _engine.get_resources();
    auto& audio = _engine.get_audio_context();
    audio.play_music(resources.get_music("weather"));

    render.render(resources.get_texture(_background_tex), 0, 0);

    _player.handleRender(resources, render, predictionRatio);

    for(auto& z : zombies()) {
        z.handle_render(resources, render, _engine.get_audio_context(), predictionRatio);
    }

    for(auto& w : werewolves()) {
        w.handle_render(resources, render, _engine.get_audio_context(), predictionRatio);
    }

    for(auto& b : bullets()) {
        b.handle_render(resources, render, predictionRatio);
    }

    render_crosshair(_mouse_x, _mouse_y, resources, render, _player, predictionRatio);

    render.refresh_screen();
}
