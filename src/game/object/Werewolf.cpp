#include "Werewolf.h"
#include <engine/geometry/maths.h>

using std::vector;

Werewolf::Werewolf(Point2<float> position)
        : _transform{Transform{position, 0.0f, 25.0f}},
          _hitpoints{Hitpoints{30}} {}

int Werewolf::get_melee_damage() const {
    // FIXME: animation has attack points on frames 3 and 7, so it's not only last frame
    if (_ai_state == AI_ATTACKING && _sprite.is_last_frame()) {
        return 10;

    } else {
        return 0;
    }
}

std::string Werewolf::get_tex_name() const {
    return _sprite.get_tex_name();
}

void Werewolf::take_damage(int damage_dealt) {
    if (_ai_state == AI_TELEPORTING) damage_dealt /= 2;

    if (damage_dealt > 0) _hitpoints.current_hp -= damage_dealt;
    if (!has_hp() && _ai_state != AI_DYING) {
        _ai_state = AI_DYING;
        _sprite.set_state(animation::WOLF_DYING);
    }
}

void Werewolf::set_target(Point2<float> position) {
    if (_ai_state == AI_DYING) return;

    if (_ai_state == AI_TELEPORTING
        && !_teleport_cooldown.ticks_passed_since_start(500)) {
        return;
    }

    _transform.angle = math::get_cartesian_angle(_transform.position, position);

    auto dist = math::get_distance(_transform.position, position);
    if (dist > get_circle().get_radius() * 1.7f) {
        if (_ai_state != AI_MOVING) {
            _ai_state = AI_MOVING;
            _sprite.set_state(animation::WOLF_MOVING);
        }
    } else if (_ai_state != AI_ATTACKING) {
        _ai_state = AI_ATTACKING;
        _sprite.set_state(animation::WOLF_ATTACKING);
    }
}

void Werewolf::handle_logic() {
    if (_ai_state == AI_DYING) {
        set_current_speed(0.f, 0.f);
        return;
    }

    if (_ai_state == AI_MOVING) {
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

    if (_ai_state == AI_ATTACKING && _attack_cooldown.ticks_passed_since_start(600)) {
        _attack_cooldown.restart();
        _ai_state = AI_MOVING;
        _sprite.set_state(animation::WOLF_MOVING);
    }
}

void Werewolf::teleport(Random& random) {
    if (_ai_state == AI_DYING) return;

    if (_ai_state != AI_TELEPORTING && _teleport_cooldown.ticks_passed_since_start(1000)) {
        _transform.position = make_point(
                _transform.position.x + random.get_int(-150, 150),
                _transform.position.y + random.get_int(-150, 150)
        );
        _ai_state = AI_TELEPORTING;
        _sprite.set_state(animation::WOLF_TELEPORT);
        _teleport_cooldown.restart();
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

    if (_ai_state == AI_ATTACKING) {
        // FIXME: Animation has attack points in 3 and 7 frames, not only last
        if (_sprite.is_last_frame()) {
            audio.play_sound("wolf_attack");
        }
        if (_attack_cooldown.ticks_passed_since_start(100)) {
            _attack_cooldown.restart();
        }

    } else if (_ai_state == AI_TELEPORTING) {
        if (_attack_cooldown.ticks_passed_since_start(100) && _sprite.is_last_frame()) {
            audio.play_sound("wolf_teleport");
        }

    }

    _sprite.update();
}

bool Werewolf::is_dead() const {
    return _ai_state == AI_DYING && _sprite.is_animation_ended();
//    return _ai_state == AI_DYING && _animation_frame == 2;
}
