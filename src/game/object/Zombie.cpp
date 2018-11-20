#include "Zombie.h"
#include <engine/geometry/maths.h>
#include <engine/log/Log.h>

using std::vector;

Zombie::Zombie(Point2<float> position)
        : _transform{Transform{position, 0.0f, 25.0f}},
          _hitpoints{Hitpoints{50}} {
}

int Zombie::get_melee_damage() const {
    if (_ai.is_attacking() && _animation.is_last_frame()) {
        return 15;
    } else {
        return 0;
    }
}

std::string Zombie::get_tex_name() const {
    return _animation.get_tex_name();
}

void Zombie::take_damage(int damage_dealt) {
    if (damage_dealt > 0) {
        _hitpoints.current_hp -= damage_dealt;
    }

    if (!has_hp() && !_ai.is_dying()) {
        _ai.set_state(ZombieAi::AI_DYING);
        _animation.set_preset(animation::ZOMBIE_DYING);
    }
}

void Zombie::set_target(Point2<float> position) {
    if (_ai.is_dying()) {
        return;
    }

    _transform.angle = math::get_cartesian_angle(_transform.position, position);

    auto dist = math::get_distance(_transform.position, position);
    if (dist > get_circle().get_radius() * 1.7f) {
        if (!_ai.is_moving()) {
            _ai.set_state(ZombieAi::AI_MOVING);
            _animation.set_preset(animation::ZOMBIE_MOVING);
        }
    } else if (!_ai.is_attacking()) {
        _ai.set_state(ZombieAi::AI_ATTACKING);
        _animation.set_preset(animation::ZOMBIE_ATTACKING);
    }
}

void Zombie::handle_logic() {
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
}

void Zombie::handle_render(Engine& engine, float frames_count) {
    default_render(engine.get_graphic(), frames_count);
    default_render_health(engine.get_graphic(), Color{0, 0x77, 0, 0xFF}, 0);

    if (_ai.is_attacking() && _animation.is_last_frame()) {
        engine.get_audio().play_sound("zombie_attack");
    }

    _animation.forward_time();
}

bool Zombie::is_dead() const {
    return _ai.is_dying() && _animation.is_last_frame();
}
