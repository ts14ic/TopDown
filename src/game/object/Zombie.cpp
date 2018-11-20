#include "Zombie.h"
#include <engine/geometry/maths.h>

using std::vector;

Zombie::Zombie(Point2<float> position)
        : _transform{Transform{position, 0.0f, 25.0f}},
          _hitpoints{Hitpoints{50}} {
}

int Zombie::get_melee_damage() const {
    if (_zombie_ai.is_attacking() && _animation.get_frame() == 5)
        return 15;
    else
        return 0;
}

std::string Zombie::get_tex_name() const {
    std::string name = "zombie";

    if (_zombie_ai.is_attacking()) {
        name += "_attack";
        name += std::to_string(_animation.get_frame());
    } else if (_zombie_ai.is_dying()) {
        name += "_death";
        name += std::to_string(_animation.get_frame());
    }

    return name;
}

void Zombie::take_damage(const Clock& clock, int damage_dealt) {
    if (damage_dealt > 0) _hitpoints.current_hp -= damage_dealt;

    if (!has_hp() && !_zombie_ai.is_dying()) {
        _zombie_ai.set_state(ZombieAi::AI_DYING);
        _animation.reset_frame();
    }
}

void Zombie::set_target(Point2<float> position) {
    if (_zombie_ai.is_dying()) return;

    _transform.angle = math::get_cartesian_angle(_transform.position, position);

    auto dist = math::get_distance(_transform.position, position);
    if (dist > get_circle().get_radius() * 1.7f) {
        if (!_zombie_ai.is_moving()) {
            _zombie_ai.set_state(ZombieAi::AI_MOVING);
            _animation.reset_frame();
        }
    } else if (!_zombie_ai.is_attacking()) {
        _zombie_ai.set_state(ZombieAi::AI_ATTACKING);
        _animation.reset_frame();
    }
}

void Zombie::handle_logic() {
    if (_zombie_ai.is_dying()) {
        set_current_speed(0.f, 0.f);
        return;
    }

    if (_zombie_ai.is_moving()) {
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
    if (_zombie_ai.is_attacking()) {
        if (_animation.get_frame() == 5) {
            audio.play_sound("zombie_attack");
        }

        if (_animation.ticks_passed_since_start(clock, 100)) {
            _animation.next_frame();
            if (_animation.get_frame() >= 6) {
                _animation.reset_frame();
            }
            _animation.reset_timer(clock);
        }
    } else if (_zombie_ai.is_dying()) {
        if (_animation.get_frame() < 7 && _animation.ticks_passed_since_start(clock, 500)) {
            _animation.next_frame();
            _animation.reset_timer(clock);
        }
    }
}

bool Zombie::is_dead() const {
    return _zombie_ai.is_dying()
           && _animation.get_frame() == 7;
}
