#include "GameObject.h"

using std::vector;

/* ======================== Bullet (Normal) ================= */

vector<Bullet>& bullets() {
    static vector<Bullet> ret;
    return ret;
}

Bullet::Bullet(Object const& shooter, Weapon const& weap)
{
    _angle = shooter.angle() + rand_float(weap.spread());
    _x = shooter.x() + dcos(_angle) * weap.length();
    _y = shooter.y() + dsin(_angle) * weap.length();
    
    _dmg   = weap.dmg();
    _speed = weap.speed();
}

float Bullet::x() const { return _x; }
float Bullet::y() const { return _y; };
float Bullet::angle() const { return _angle; }
float Bullet::speed() const { return _speed; }

void Bullet::x(float x) { _x = x; }
void Bullet::y(float y) { _y = y; };
void Bullet::angle(float a) { _angle = a; }
void Bullet::speed(float s) { _speed = s; }

std::string Bullet::texName() const { return "bullet"; }

void Bullet::handle_logic() {
    default_move();
}

void Bullet::handle_render() {
    default_render();
}
