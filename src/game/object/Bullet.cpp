#include "Bullet.h"
#include "math/maths.h"

using std::vector;

vector<Bullet>& bullets() {
    static vector<Bullet> ret;
    return ret;
}

Bullet::Bullet(Random& random, const GameObject& shooter, const Weapon& weapon) {
    float half = weapon.get_projectile_spread() / 2;
    _angle = shooter.get_angle() + random.get_float(-half, half);
    _position = make_point(
            shooter.get_position().x + math::cartesian_cos(_angle) * weapon.get_length(),
            shooter.get_position().y + math::cartesian_sin(_angle) * weapon.get_length()
    );
    _damage = weapon.get_projectile_damage();
    _max_speed = weapon.get_projectile_speed();
}

float Bullet::get_angle() const { return _angle; }

float Bullet::get_max_movement_speed() const { return _max_speed; }

void Bullet::set_angle(float a) { _angle = a; }

void Bullet::set_max_movement_speed(float s) { _max_speed = s; }

int Bullet::get_damage() const { return _damage; }

Circle Bullet::get_circle() const { return {_position, 2}; }

std::string Bullet::get_tex_name() const { return "bullet"; }

void Bullet::handle_logic() {
    {
        // TODO extract speed setting
        auto movementAngle = get_angle();

        float x_speed = math::cartesian_cos(movementAngle) * get_max_movement_speed();
        float y_speed = math::cartesian_sin(movementAngle) * get_max_movement_speed();

        set_current_x_speed(x_speed);
        set_current_y_speed(y_speed);
    }

    default_move();
}

void Bullet::handle_render(Engine& engine, Graphic& graphic, float frames_count) {
    default_render(graphic, frames_count);
}

float Bullet::get_current_x_speed() const {
    return _current_x_speed;
}

float Bullet::get_current_y_speed() const {
    return _current_y_speed;
}

void Bullet::set_current_x_speed(float x_speed) {
    _current_x_speed = x_speed;
}

void Bullet::set_current_y_speed(float y_speed) {
    _current_y_speed = y_speed;
}

void Bullet::set_current_speed(float x_speed, float y_speed) {
    set_current_x_speed(x_speed);
    set_current_y_speed(y_speed);
}
