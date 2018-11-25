#include "Bullet.h"
#include <engine/geometry/maths.h>

using std::vector;

Bullet::Bullet(Random& random, const Transform& origin, const Weapon& weapon) {
    float half = weapon.get_projectile_spread() / 2;
    _transform.angle = origin.angle + random.get_float(-half, half);
    _transform.position = make_point(
            origin.position.x + math::cartesian_cos(_transform.angle) * weapon.get_length(),
            origin.position.y + math::cartesian_sin(_transform.angle) * weapon.get_length()
    );
    _transform.radius = 2.0f;
    _damage = weapon.get_projectile_damage();
    _speed.max_speed = weapon.get_projectile_speed();
}

int Bullet::get_melee_damage() const { return _damage; }

std::string Bullet::get_tex_name() const { return "bullet"; }

void Bullet::handle_render(Graphic& graphic, float frames_count) {
    default_render(graphic, frames_count);
}
