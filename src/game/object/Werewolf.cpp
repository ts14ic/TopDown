#include "Werewolf.h"
#include <engine/geometry/maths.h>

using std::vector;

Werewolf::Werewolf(Point2<float> position)
        : _transform{Transform{position, 0.0f, 25.0f}},
          _hitpoints{Hitpoints{30}} {}

int Werewolf::get_damage() const {
    if (_ai_state == AI_ATTACKING && (_animation_frame == 3 || _animation_frame == 7))
        return 10;
    else return 0;
}

std::string Werewolf::get_tex_name() const {
    std::string name = "wolf";

    if (_ai_state == AI_ATTACKING) {
        name += "_attack";
        name += std::to_string(_animation_frame);
    } else if (_ai_state == AI_TELEPORTING) {
        name += "_teleport";
        name += std::to_string(_animation_frame);
    } else if (_ai_state == AI_DYING) {
        name += "_teleport";
        name += std::to_string(_animation_frame);
    } else {
        name += "_move";
        name += std::to_string(_animation_frame);
    }

    return name;
}

void Werewolf::damage(const Clock& clock, int damage_dealt) {
    if (_ai_state == AI_TELEPORTING) damage_dealt /= 2;

    if (damage_dealt > 0) _hitpoints.current_hp -= damage_dealt;
    if (!has_hp() && _ai_state != AI_DYING) {
        _ai_state = AI_DYING;
        _animation_frame = 0;
    }
}

void Werewolf::set_target(const Clock& clock, Point2<float> position) {
    if (_ai_state == AI_DYING) return;

    if (_ai_state == AI_TELEPORTING
        && !_teleport_cooldown.ticks_passed_since_start(clock, 500)) {
        return;
    }

    _transform.angle = math::get_cartesian_angle(_transform.position, position);

    auto dist = math::get_distance(_transform.position, position);
    if (dist > get_circle().get_radius() * 1.7f) {
        if (_ai_state != AI_MOVING) {
            _ai_state = AI_MOVING;
            _animation_frame = 0;
        }
    } else if (_ai_state != AI_ATTACKING) {
        _ai_state = AI_ATTACKING;
        _animation_frame = 0;
    }
}

void Werewolf::handle_logic(const Clock& clock) {
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

    if (_ai_state == AI_ATTACKING && _attack_cooldown.ticks_passed_since_start(clock, 600)) {
        _attack_cooldown.restart(clock);
        _ai_state = AI_MOVING;
        _animation_frame = 0;
    }
}

void Werewolf::teleport(const Clock& clock, Random& random) {
    if (_ai_state == AI_DYING) return;

    if (_ai_state != AI_TELEPORTING && _teleport_cooldown.ticks_passed_since_start(clock, 1000)) {
        _transform.position = make_point(
                _transform.position.x + random.get_int(-150, 150),
                _transform.position.y + random.get_int(-150, 150)
        );
        _ai_state = AI_TELEPORTING;
        _animation_frame = 0;
        _teleport_cooldown.restart(clock);
    }
}

void Werewolf::handle_render(Engine& engine, Graphic& graphic_context, Audio& audio,
                             float frames_count) {
    default_render(graphic_context, frames_count);

    if (has_hp()) {
        Box health_box;
        health_box.set_size(1.66f * _hitpoints.current_hp, 5);
        health_box.set_left_top(
                _transform.position.x - health_box.get_width() / 2,
                _transform.position.y - get_circle().get_radius()
        );
        graphic_context.render_box(health_box, Color{0x55, 0, 0x33});
    }

    const auto& clock = engine.get_clock();
    // TODO Wow, wow, wow. Fix all the repetition
    if (_ai_state == AI_ATTACKING) {
        if (_animation_frame == 3 || _animation_frame == 7) {
            audio.play_sound("wolf_attack");
        }

        if (_attack_cooldown.ticks_passed_since_start(clock, 100)) {
            ++_animation_frame;
            if (_animation_frame >= 8) _animation_frame = 0;
            _attack_cooldown.restart(clock);
        }
    } else if (_ai_state == AI_MOVING) {
        if (_attack_cooldown.ticks_passed_since_start(clock, 100)) {
            ++_animation_frame;
            if (_animation_frame >= 6) _animation_frame = 0;
            _attack_cooldown.restart(clock);
        }
    } else if (_ai_state == AI_TELEPORTING) {
        if (_attack_cooldown.ticks_passed_since_start(clock, 100)) {
            if (_animation_frame == 2) {
                audio.play_sound("wolf_teleport");
            }

            ++_animation_frame;
            if (_animation_frame > 2) _animation_frame = 0;
            _attack_cooldown.restart(clock);
        }
    } else if (_ai_state == AI_DYING) {
        if (_animation_frame < 2 && _attack_cooldown.ticks_passed_since_start(clock, 500)) {
            ++_animation_frame;
            _attack_cooldown.restart(clock);
        }
    }
}

bool Werewolf::is_dead() const {
    return _ai_state == AI_DYING && _animation_frame == 2;
}

vector<Werewolf>& werewolves() {
    static vector<Werewolf> ret;
    return ret;
}
