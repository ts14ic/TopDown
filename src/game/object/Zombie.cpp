#include "Zombie.h"
#include <engine/geometry/maths.h>

using std::vector;

Zombie::Zombie(Point2<float> position)
        : _transform{Transform{position, 0.0f, 25.0f}},
          _hitpoints{Hitpoints{50}} {
}

int Zombie::get_damage() const { if (_ai_state == AI_ATTACKING && _animation_frame == 5) return 15; else return 0; }

std::string Zombie::get_tex_name() const {
    std::string name = "zombie";

    if (_ai_state == AI_ATTACKING) {
        name += "_attack";
        name += std::to_string(_animation_frame);
    } else if (_ai_state == AI_DYING) {
        name += "_death";
        name += std::to_string(_animation_frame);
    }

    return name;
}

void Zombie::take_damage(const Clock& clock, int damage_dealt) {
    if (damage_dealt > 0) _hitpoints.current_hp -= damage_dealt;

    if (!has_hp() && _ai_state != AI_DYING) {
        _ai_state = AI_DYING;
        _animation_frame = 0;
    }
}

void Zombie::set_target(Point2<float> position) {
    if (_ai_state == AI_DYING) return;

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

void Zombie::handle_logic() {
    if (_ai_state == AI_DYING) {
        set_current_speed(0.f, 0.f);
        return;
    }

    if (_ai_state == AI_MOVING) {
        // TODO extract speed setting
        auto movementAngle = get_angle();

        set_current_speed(
                math::cartesian_cos(movementAngle) * get_max_movement_speed(),
                math::cartesian_sin(movementAngle) * get_max_movement_speed()
        );
        default_move();
    } else {
        set_current_speed(0.f, 0.f);
    }
}

void Zombie::handle_render(Engine& engine, Graphic& graphic, Audio& audio,
                           float frames_count) {
    default_render(graphic, frames_count);
    default_render_health(graphic, Color{0, 0x77, 0, 0xFF}, 0);

    const auto& clock = engine.get_clock();
    if (_ai_state == AI_ATTACKING) {
        if (_animation_frame == 5) {
            audio.play_sound("zombie_attack");
        }

        if (_animation_timer.ticks_passed_since_start(clock, 100)) {
            ++_animation_frame;
            if (_animation_frame >= 6) _animation_frame = 0;
            _animation_timer.restart(clock);
        }
    } else if (_ai_state == AI_DYING) {
        if (_animation_frame < 7 && _animation_timer.ticks_passed_since_start(clock, 500)) {
            ++_animation_frame;
            _animation_timer.restart(clock);
        }
    }
}

bool Zombie::is_dead() const {
    return _ai_state == AI_DYING && _animation_frame == 7;
}

vector<Zombie>& zombies() {
    static vector<Zombie> ret;
    return ret;
}
