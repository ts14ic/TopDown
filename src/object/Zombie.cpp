#include "Zombie.h"
#include "../shape/Circle.h"
#include "../shape/Color.h"
#include "../math/math.h"
#include "../resources/Resources.h"
#include "../resources/Sound.h"

using std::vector;

Zombie::Zombie(int x, int y)
        : mX(x), mY(y) {
    mCurrentHp = Zombie::defaultHp();
}

float Zombie::getX() const { return mX; }

float Zombie::getY() const { return mY; }

void Zombie::setX(float x) { mX = x; }

void Zombie::setY(float y) { mY = y; }

float Zombie::getAngle() const { return mAngle; }

float Zombie::getMaxMovementSpeed() const { return mSpeed; }

void Zombie::setAngle(float a) { mAngle = a; }

void Zombie::setMaxMovementSpeed(float s) { mSpeed = s; }

Circle Zombie::getCircle() const { return {mX, mY, 25}; }

int Zombie::hp() const { return mCurrentHp; }

int Zombie::defaultHp() const { return 50; }

int Zombie::dmg() const { if(mAiState == ATTACKING && mAnimationFrame == 5) return 15; else return 0; }

std::string Zombie::getTexName() const {
    std::string name = "zombie";

    if(mAiState == ATTACKING) {
        name += "_attack";
        name += std::to_string(mAnimationFrame);
    } else if(mAiState == DYING) {
        name += "_death";
        name += std::to_string(mAnimationFrame);
    }

    return name;
}

void Zombie::damage(const Clock& clock, int d) {
    if(d > 0) mCurrentHp -= d;

    if(mCurrentHp <= 0 && mAiState != DYING) {
        mAiState = DYING;
        mAnimationFrame = 0;
    }
}

void Zombie::set_target(float x, float y, bool ignore) {
    if(ignore || mAiState == DYING) return;

    mAngle = toCartesian(::getAngle(mX, mY, x, y));

    auto dist = getDistance(mX, mY, x, y);
    if(dist > getCircle().getRadius() * 1.7f) {
        if(mAiState != MOVING) {
            mAiState = MOVING;
            mAnimationFrame = 0;
        }
    } else if(mAiState != ATTACKING) {
        mAiState = ATTACKING;
        mAnimationFrame = 0;
    }
}

void Zombie::handle_logic() {
    if(mAiState == DYING) {
        setCurrentSpeed(0, 0);
        return;
    }

    if(mAiState == MOVING) {
        // TODO extract speed setting
        auto movementAngle = getAngle();

        float speedX = cartesianCos(movementAngle) * getMaxMovementSpeed();
        float speedY = cartesianSin(movementAngle) * getMaxMovementSpeed();

        setCurrentSpeed(speedX, speedY);
        defaultMove();
    } else {
        setCurrentSpeed(0.f, 0.f);
    }
}

void Zombie::handleRender(Resources& resources, GraphicContext& graphicContext, AudioContext& audioContext,
                          float predictionRatio) {
    defaultRender(resources, graphicContext, predictionRatio);
    defaultRenderHealth(graphicContext, Color{0, 0x77, 0, 0xFF}, 0);

    const auto& clock = resources.getClock();
    if(mAiState == ATTACKING) {
        if(mAnimationFrame == 5) {
            audioContext.playSound(resources.getSound("zombie_attack"));
        }

        if(mTimer.haveTicksPassedSinceStart(clock, 100)) {
            ++mAnimationFrame;
            if(mAnimationFrame >= 6) mAnimationFrame = 0;
            mTimer.restart(clock);
        }
    } else if(mAiState == DYING) {
        if(mAnimationFrame < 7 && mTimer.haveTicksPassedSinceStart(clock, 500)) {
            ++mAnimationFrame;
            mTimer.restart(clock);
        }
    }
}

bool Zombie::dead() const {
    return mAiState == DYING && mAnimationFrame == 7;
}

void Zombie::setPos(float x, float y) {
    setX(x);
    setY(y);
}

float Zombie::getCurrentSpeedX() const {
    return mCurrentSpeedX;
}

float Zombie::getCurrentSpeedY() const {
    return mCurrentSpeedY;
}

void Zombie::setCurrentSpeedX(float speedX) {
    mCurrentSpeedX = speedX;
}

void Zombie::setCurrentSpeedY(float speedY) {
    mCurrentSpeedY = speedY;
}

void Zombie::setCurrentSpeed(float speedX, float speedY) {
    setCurrentSpeedX(speedX);
    setCurrentSpeedY(speedY);
}

vector<Zombie>& zombies() {
    static vector<Zombie> ret;
    return ret;
}
