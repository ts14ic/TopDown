#include "Werewolf.h"
#include <engine/geometry/maths.h>

using std::vector;

Werewolf::Werewolf(Point2<float> position)
        : _transform{Transform{position, 0.0f, 25.0f}},
          _hitpoints{Hitpoints{30}} {}

int Werewolf::get_melee_damage() const {
    if (_ai.is_attacking() && _ai.can_deal_damage()) {
        return 10;

    } else {
        return 0;

    }
}

std::string Werewolf::get_tex_name() const {
    return _sprite.get_tex_name();
}

void Werewolf::take_damage(int damage_dealt) {
    if (_ai.is_teleporting()) {
        damage_dealt /= 2;
    }

    if (damage_dealt > 0) _hitpoints.current_hp -= damage_dealt;
    if (!has_hp() && !_ai.is_dying()) {
        _ai.set_state(WolfAi::AI_DYING);
        _sprite.set_state(animation::WOLF_DYING);
    }
}

void Werewolf::set_target(Point2<float> position) {
    if (_ai.is_dying()) {
        return;
    }

    if (_ai.is_teleporting() && !_ai.teleport_finished()) {
        return;
    }

    _transform.angle = math::get_cartesian_angle(_transform.position, position);

    auto dist = math::get_distance(_transform.position, position);
    if (dist > get_circle().get_radius() * 1.7f) {
        if (!_ai.is_moving()) {
            _ai.set_state(WolfAi::AI_MOVING);
            _sprite.set_state(animation::WOLF_MOVING);
        }
    } else if (!_ai.is_attacking()) {
        _ai.set_state(WolfAi::AI_ATTACKING);
        _sprite.set_state(animation::WOLF_ATTACKING);
    }
}

void Werewolf::handle_logic() {
    if (_ai.is_dying()) {
        set_current_speed(0.f, 0.f);
        return;
    }

    if (_ai.is_moving()) {
        // TODO extract speed setting
        auto movement_angle = get_angle();

        set_current_speed(
                math::cartesian_cos(movement_angle) * get_max_movement_speed(),
                math::cartesian_sin(movement_angle) * get_max_movement_speed()
        );
        default_move();
    } else {
        set_current_speed(0.f, 0.f);
    }

    if (_ai.is_attacking() && _ai.must_reset_attack()) {
        _ai.restart_attack();
    }
}

void Werewolf::teleport(Random& random) {
    if (_ai.is_dying()) {
        return;
    }

    if (!_ai.is_teleporting() && _ai.can_teleport()) {
        _transform.position = make_point(
                _transform.position.x + random.get_int(-150, 150),
                _transform.position.y + random.get_int(-150, 150)
        );
        _ai.set_state(WolfAi::AI_TELEPORTING);
        _ai.teleport_restart();
        _sprite.set_state(animation::WOLF_TELEPORT);
    }
}

void Werewolf::handle_render(Engine& engine, Graphic& graphic, Audio& audio,
                             float frames_count) {
    default_render(graphic, frames_count);

    if (has_hp()) {
        Box health_box;
        health_box.set_size(1.66f * _hitpoints.current_hp, 5);
        health_box.set_left_top(
                _transform.position.x - health_box.get_width() / 2,
                _transform.position.y - get_circle().get_radius()
        );
        graphic.render_box(health_box, Color{0x55, 0, 0x33});
    }

    if (_ai.is_attacking()) {
        // FIXME: Animation has attack points in 3 and 7 frames, not only last
        if (_sprite.is_last_frame()) {
            audio.play_sound("wolf_attack");
        }

    } else if (_ai.is_teleporting()) {
        if (_sprite.is_last_frame()) {
            audio.play_sound("wolf_teleport");
        }

    }

    _sprite.update();
}

bool Werewolf::is_dead() const {
    return _ai.is_dying() && _sprite.is_animation_ended();
}
