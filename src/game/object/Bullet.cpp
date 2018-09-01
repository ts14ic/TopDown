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
    _x = shooter.get_x() + math::cartesian_cos(_angle) * weapon.get_length();
    _y = shooter.get_y() + math::cartesian_sin(_angle) * weapon.get_length();

    _damage = weapon.get_projectile_damage();
    _max_speed = weapon.get_projectile_speed();
}

float Bullet::get_x() const { return _x; }

float Bullet::get_y() const { return _y; }

float Bullet::get_angle() const { return _angle; }

float Bullet::get_max_movement_speed() const { return _max_speed; }

void Bullet::set_x(float x) { _x = x; }

void Bullet::set_y(float y) { _y = y; }

void Bullet::set_angle(float a) { _angle = a; }

void Bullet::set_max_movement_speed(float s) { _max_speed = s; }

int Bullet::get_damage() const { return _damage; }

Circle Bullet::get_circle() const { return {_x, _y, 2}; }

std::string Bullet::get_tex_name() const { return "bullet"; }

void Bullet::handle_logic() {
    {
        // TODO extract speed setting
        auto movementAngle = get_angle();

        float speedX = math::cartesian_cos(movementAngle) * get_max_movement_speed();
        float speedY = math::cartesian_sin(movementAngle) * get_max_movement_speed();

        set_current_speed_x(speedX);
        set_current_speed_y(speedY);
    }

    default_move();
}

void Bullet::handle_render(Engine& engine, Graphic& graphic, float predictionRatio) {
    default_render(graphic, predictionRatio);
}

void Bullet::set_position(float x, float y) {
    set_x(x);
    set_y(y);
}

float Bullet::get_current_speed_x() const {
    return _current_speed_x;
}

float Bullet::get_current_speed_y() const {
    return _current_speed_y;
}

void Bullet::set_current_speed_x(float speedX) {
    _current_speed_x = speedX;
}

void Bullet::set_current_speed_y(float speedY) {
    _current_speed_y = speedY;
}

void Bullet::set_current_speed(float speedX, float speedY) {
    set_current_speed_x(speedX);
    set_current_speed_y(speedY);
}
