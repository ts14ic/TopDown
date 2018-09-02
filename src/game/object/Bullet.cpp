#include "Bullet.h"
#include <engine/geometry/maths.h>

using std::vector;

vector<Bullet>& bullets() {
    static vector<Bullet> ret;
    return ret;
}

Bullet::Bullet(Random& random, const GameObject& shooter, const Weapon& weapon) {
    float half = weapon.get_projectile_spread() / 2;
    _transform.angle = shooter.get_angle() + random.get_float(-half, half);
    _transform.position = make_point(
            shooter.get_position().x + math::cartesian_cos(_transform.angle) * weapon.get_length(),
            shooter.get_position().y + math::cartesian_sin(_transform.angle) * weapon.get_length()
    );
    _transform.radius = 2.0f;
    _damage = weapon.get_projectile_damage();
    _speed.max_speed = weapon.get_projectile_speed();
}

int Bullet::get_damage() const { return _damage; }

std::string Bullet::get_tex_name() const { return "bullet"; }

void Bullet::handle_logic() {
    {
        // TODO extract speed setting
        auto movement_angle = get_angle();

        set_current_speed(
                math::cartesian_cos(movement_angle) * get_max_movement_speed(),
                math::cartesian_sin(movement_angle) * get_max_movement_speed()
        );
    }

    default_move();
}

void Bullet::handle_render(Engine& engine, Graphic& graphic, float frames_count) {
    default_render(graphic, frames_count);
}
