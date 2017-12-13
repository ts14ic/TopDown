#include "Bullet.h"
#include "../engine/Random.h"
#include "../shape/Circle.h"
#include "../math/math.h"
#include "Weapon.h"

using std::vector;

vector<Bullet>& bullets() {
    static vector<Bullet> ret;
    return ret;
}

Bullet::Bullet(Random& random, GameObject const& shooter, Weapon const& weap) {
    float half = weap.getProjectileSpread() / 2;
    _angle = shooter.getAngle() + random.getFloat(-half, half);
    _x = shooter.getX() + cartesianCos(_angle) * weap.getLength();
    _y = shooter.getY() + cartesianSin(_angle) * weap.getLength();

    _dmg = weap.getProjectileDamage();
    _speed = weap.getProjectileSpeed();
}

float Bullet::getX() const { return _x; }

float Bullet::getY() const { return _y; }

float Bullet::getAngle() const { return _angle; }

float Bullet::getSpeed() const { return _speed; }

void Bullet::setX(float x) { _x = x; }

void Bullet::setY(float y) { _y = y; }

void Bullet::setAngle(float a) { _angle = a; }

void Bullet::setSpeed(float s) { _speed = s; }

int Bullet::dmg() const { return _dmg; }

Circle Bullet::getCircle() const { return {_x, _y, 2}; }

std::string Bullet::getTexName() const { return "bullet"; }

void Bullet::handle_logic() {
    default_move();
}

void Bullet::handle_render(Resources& resources, GraphicContext& graphicContext) {
    default_render(resources, graphicContext);
}

void Bullet::setPos(float x, float y) {
    setX(x);
    setY(y);
}
