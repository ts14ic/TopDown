#include "Bullet.h"
#include "../../engine/Random.h"
#include "../../shape/Circle.h"
#include "../../utils/math/math.h"
#include "Weapon.h"

using std::vector;

vector<Bullet>& bullets() {
    static vector<Bullet> ret;
    return ret;
}

Bullet::Bullet(Random& random, GameObject const& shooter, Weapon const& weap) {
    float half = weap.getProjectileSpread() / 2;
    mAngle = shooter.getAngle() + random.getFloat(-half, half);
    mX = shooter.getX() + math::cartesianCos(mAngle) * weap.getLength();
    mY = shooter.getY() + math::cartesianSin(mAngle) * weap.getLength();

    mDamage = weap.getProjectileDamage();
    mMaxSpeed = weap.getProjectileSpeed();
}

float Bullet::getX() const { return mX; }

float Bullet::getY() const { return mY; }

float Bullet::getAngle() const { return mAngle; }

float Bullet::getMaxMovementSpeed() const { return mMaxSpeed; }

void Bullet::setX(float x) { mX = x; }

void Bullet::setY(float y) { mY = y; }

void Bullet::setAngle(float a) { mAngle = a; }

void Bullet::setMaxMovementSpeed(float s) { mMaxSpeed = s; }

int Bullet::dmg() const { return mDamage; }

Circle Bullet::getCircle() const { return {mX, mY, 2}; }

std::string Bullet::getTexName() const { return "bullet"; }

void Bullet::handle_logic() {
    {
        // TODO extract speed setting
        auto movementAngle = getAngle();

        float speedX = math::cartesianCos(movementAngle) * getMaxMovementSpeed();
        float speedY = math::cartesianSin(movementAngle) * getMaxMovementSpeed();

        setCurrentSpeedX(speedX);
        setCurrentSpeedY(speedY);
    }

    defaultMove();
}

void Bullet::handleRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio) {
    defaultRender(resources, graphicContext, predictionRatio);
}

void Bullet::setPos(float x, float y) {
    setX(x);
    setY(y);
}

float Bullet::getCurrentSpeedX() const {
    return mCurrentSpeedX;
}

float Bullet::getCurrentSpeedY() const {
    return mCurrentSpeedY;
}

void Bullet::setCurrentSpeedX(float speedX) {
    mCurrentSpeedX = speedX;
}

void Bullet::setCurrentSpeedY(float speedY) {
    mCurrentSpeedY = speedY;
}

void Bullet::setCurrentSpeed(float speedX, float speedY) {
    setCurrentSpeedX(speedX);
    setCurrentSpeedY(speedY);
}
