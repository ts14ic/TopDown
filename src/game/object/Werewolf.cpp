#include "Werewolf.h"
#include "../../shape/Circle.h"
#include "../../shape/Box.h"
#include "../../shape/Color.h"
#include "../../utils/math/math.h"
#include "../../engine/GraphicContext.h"
#include "../../engine/Random.h"
#include "../../engine/resources/Resources.h"
#include "../../engine/resources/Sound.h"

using std::vector;

Werewolf::Werewolf(float x, float y)
        : mX{x}, mY{y} {
    mCurrentHp = Werewolf::defaultHp();
}

// GameObject legacy
float Werewolf::getX() const { return mX; }

float Werewolf::getY() const { return mY; }

void Werewolf::setX(float x) { mX = x; }

void Werewolf::setY(float y) { mY = y; }

float Werewolf::getAngle() const { return mViewAngle; }

float Werewolf::getMaxMovementSpeed() const { return mMaxMovementSpeed; }

void Werewolf::setAngle(float a) { mViewAngle = a; }

void Werewolf::setMaxMovementSpeed(float s) { mMaxMovementSpeed = s; }

Circle Werewolf::getCircle() const { return {mX, mY, 25}; }

int Werewolf::hp() const { return mCurrentHp; }

int Werewolf::defaultHp() const { return 30; }

int Werewolf::dmg() const {
    if(mAiState == ATTACKING && (mAnimationFrame == 3 || mAnimationFrame == 7))
        return 10;
    else return 0;
}

std::string Werewolf::getTexName() const {
    std::string name = "wolf";

    if(mAiState == ATTACKING) {
        name += "_attack";
        name += std::to_string(mAnimationFrame);
    } else if(mAiState == TELEPORTING) {
        name += "_teleport";
        name += std::to_string(mAnimationFrame);
    } else if(mAiState == DYING) {
        name += "_teleport";
        name += std::to_string(mAnimationFrame);
    } else {
        name += "_move";
        name += std::to_string(mAnimationFrame);
    }

    return name;
}

void Werewolf::damage(const Clock& clock, int d) {
    if(mAiState == TELEPORTING) d /= 2;

    if(d > 0) mCurrentHp -= d;
    if(mCurrentHp <= 0 && mAiState != DYING) {
        mAiState = DYING;
        mAnimationFrame = 0;
    }
}

void Werewolf::set_target(const Clock& clock, float x, float y, bool ignore) {
    if(ignore || mAiState == DYING) return;

    if(mAiState == TELEPORTING) {
        if(!mTeleportCooldown.haveTicksPassedSinceStart(clock, 500)) return;
    }

    setAngle(math::toCartesian(math::getAngle(mX, mY, x, y)));

    auto dist = math::getDistance(mX, mY, x, y);
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

void Werewolf::handleLogic(const Clock& clock) {
    if(mAiState == DYING) {
        setCurrentSpeed(0, 0);
        return;
    }

    if(mAiState == MOVING) {
        // TODO extract speed setting
        auto movementAngle = getAngle();

        float speedX = math::cartesianCos(movementAngle) * getMaxMovementSpeed();
        float speedY = math::cartesianSin(movementAngle) * getMaxMovementSpeed();

        setCurrentSpeed(speedX, speedY);
        defaultMove();
    } else {
        setCurrentSpeed(0.f, 0.f);
    }

    if(mAiState == ATTACKING && mAttackCooldown.haveTicksPassedSinceStart(clock, 600)) {
        mAttackCooldown.restart(clock);
        mAiState = MOVING;
        mAnimationFrame = 0;
    }
}

void Werewolf::teleport(const Clock& clock, Random& random) {
    if(mAiState == DYING) return;

    if(mAiState != TELEPORTING && mTeleportCooldown.haveTicksPassedSinceStart(clock, 1000)) {
        mX += random.getInt(-150, 150);
        mY += random.getInt(-150, 150);
        mAiState = TELEPORTING;
        mAnimationFrame = 0;
        mTeleportCooldown.restart(clock);
    }
}

void Werewolf::handleRender(Resources& resources, GraphicContext& graphicContext, AudioContext& audioContext,
                            float predictionRatio) {
    defaultRender(resources, graphicContext, predictionRatio);

    if(mCurrentHp > 0) {
        Box healthBox;
        healthBox.setSize(1.66f * mCurrentHp, 5);
        healthBox.setPosition(mX - healthBox.getWidth() / 2, mY - getCircle().getRadius());
        graphicContext.renderBox(healthBox, Color{0x55, 0, 0x33});
    }

    const auto& clock = resources.getClock();
    // TODO Wow, wow, wow. Fix all the repetition
    if(mAiState == ATTACKING) {
        if(mAnimationFrame == 3 || mAnimationFrame == 7) {
            audioContext.playSound(resources.getSound("wolf_attack"));
        }

        if(mAttackCooldown.haveTicksPassedSinceStart(clock, 100)) {
            ++mAnimationFrame;
            if(mAnimationFrame >= 8) mAnimationFrame = 0;
            mAttackCooldown.restart(clock);
        }
    } else if(mAiState == MOVING) {
        if(mAttackCooldown.haveTicksPassedSinceStart(clock, 100)) {
            ++mAnimationFrame;
            if(mAnimationFrame >= 6) mAnimationFrame = 0;
            mAttackCooldown.restart(clock);
        }
    } else if(mAiState == TELEPORTING) {
        if(mAttackCooldown.haveTicksPassedSinceStart(clock, 100)) {
            if(mAnimationFrame == 2) {
                audioContext.playSound(resources.getSound("wolf_teleport"));
            }

            ++mAnimationFrame;
            if(mAnimationFrame > 2) mAnimationFrame = 0;
            mAttackCooldown.restart(clock);
        }
    } else if(mAiState == DYING) {
        if(mAnimationFrame < 2 && mAttackCooldown.haveTicksPassedSinceStart(clock, 500)) {
            ++mAnimationFrame;
            mAttackCooldown.restart(clock);
        }
    }
}

bool Werewolf::dead() const {
    return mAiState == DYING && mAnimationFrame == 2;
}

void Werewolf::setPos(float x, float y) {
    setX(x);
    setY(y);
}

float Werewolf::getCurrentSpeedX() const {
    return mCurrentSpeedX;
}

float Werewolf::getCurrentSpeedY() const {
    return mCurrentSpeedY;
}

void Werewolf::setCurrentSpeedX(float speedX) {
    mCurrentSpeedX = speedX;
}

void Werewolf::setCurrentSpeedY(float speedY) {
    mCurrentSpeedY = speedY;
}

void Werewolf::setCurrentSpeed(float speedX, float speedY) {
    setCurrentSpeedX(speedX);
    setCurrentSpeedY(speedY);
}

vector<Werewolf>& werewolves() {
    static vector<Werewolf> ret;
    return ret;
}
