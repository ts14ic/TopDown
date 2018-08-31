#include "Player.h"
#include "utils/math/maths.h"
#include <sstream>
#include <cmath>

Player::Player()
        : Player{0, 0} {}

Player::Player(int x, int y)
        : mX(x), mY(y) {
    _hp = Player::defaultHp();
}

void Player::setPos(float x, float y) {
    mX = x;
    mY = y;
}

float Player::getX() const { return mX; }

float Player::getY() const { return mY; }

float Player::getAngle() const { return mAngle; }

float Player::getMaxMovementSpeed() const {
    return mMaxMovementSpeed;
}

void Player::setX(float x) { mX = x; }

void Player::setY(float y) { mY = y; }

void Player::setAngle(float a) { mAngle = a; }

void Player::setMaxMovementSpeed(float movementSpeed) {
    if(std::isgreaterequal(movementSpeed, 0.f)) {
        mMaxMovementSpeed = movementSpeed;
    }
}

Circle Player::getCircle() const { return {mX, mY, 30}; }

std::string Player::getTexName() const {
    if(mWeapons.empty() || mSelectedWeaponIdx >= mWeapons.size()) {
        return "player";
    } else {
        std::ostringstream ostringstream;
        ostringstream << "player_" << mWeapons[mSelectedWeaponIdx].getName();
        return ostringstream.str();
    }
}

int Player::hp() const { return _hp; }

int Player::defaultHp() const { return 100; }

int Player::dmg() const { return 0; }

bool Player::dead() const {
    return _hp <= 0;
}

void Player::damage(const Clock& clock, int damageAmount) {
    if(damageAmount > 0 && mDamageCooldown.haveTicksPassedSinceStart(clock, 500)) {
        _hp -= damageAmount;
        mDamageCooldown.restart(clock);
    }
}

bool Player::reloading() const {
    return !mWeapons.empty() && mWeapons[mSelectedWeaponIdx].isReloading();
}

void Player::handleKeyEvent(const KeyboardEvent& event) {
    if(event.getType() == KeyboardEvent::Type::KeyDown) {
        switch(event.getKey()) {
            case KEY_UP:
            case 'w': {
                mInputState.set(UP_PRESSED);
                break;
            }

            case KEY_DOWN:
            case 's': {
                mInputState.set(DOWN_PRESSED);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                mInputState.set(LEFT_PRESSED);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                mInputState.set(RIGHT_PRESSED);
                break;
            }

            case KEY_SPACE: {
                mInputState.set(TRIGGER_PRESSED);
                break;
            }

            default: {
                break;
            }
        }
    } else if(event.getType() == KeyboardEvent::Type::KeyUp) {
        switch(event.getKey()) {
            case KEY_UP:
            case 'w': {
                mInputState.reset(UP_PRESSED);
                break;
            }

            case KEY_DOWN:
            case 's': {
                mInputState.reset(DOWN_PRESSED);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                mInputState.reset(LEFT_PRESSED);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                mInputState.reset(RIGHT_PRESSED);
                break;
            }

            case KEY_SPACE: {
                mInputState.reset(TRIGGER_PRESSED);
                break;
            }

            default: {
                int key = event.getKey();
                if(key >= '0' && key <= '9') {
                    auto idx = 9U - ('9' - key);
                    selectWeapon(idx);
                }
                break;
            }
        }
    }
}


void Player::handleMouseEvent(const MouseEvent& event) {
    switch(event.getType()) {
        case MouseEvent::Type::ScrollUp: {
            selectPreviousWeapon();
            break;
        }

        case MouseEvent::Type::ScrollDown: {
            selectNextWeapon();
            break;
        }

        case MouseEvent::Type::ButtonDown: {
            mInputState.set(TRIGGER_PRESSED);
            break;
        }

        case MouseEvent::Type::ButtonUp: {
            mInputState.reset(TRIGGER_PRESSED);
            break;
        }

        case MouseEvent::Type::Motion: {
            mAngle = math::getCartesianAngle(getX(), getY(), event.getX(), event.getY());
            break;
        }
    }
}

void Player::handle_logic(Random& random, Resources& resources, AudioContext& audioContext) {
    // TODO Make the timer store a pointer to clock
    // TODO AFTER Move the condition inside the getter
    setMaxMovementSpeed(mDamageCooldown.haveTicksPassedSinceStart(resources.getClock(), 500) ? 2.3f : 1.0f);

    setSpeeds();

    defaultMove();

    if(!mWeapons.empty()) {
        // TODO don't try to reload on every frame
        mWeapons[mSelectedWeaponIdx].tryReload(resources.getClock());
        if(mInputState.test(TRIGGER_PRESSED)) {
            mWeapons[mSelectedWeaponIdx].pullTrigger(random, resources, audioContext, *this);
        }
    }
}

void Player::setSpeeds() {
    // TODO extract speed calculations to share between classes
    int directionX = mInputState.test(RIGHT_PRESSED) - mInputState.test(LEFT_PRESSED);
    int directionY = mInputState.test(DOWN_PRESSED) - mInputState.test(UP_PRESSED);

    if(directionX != 0 || directionY != 0) {
        auto movementAngle = math::getRadianAngle(0, 0, directionX, directionY);

        float speedX = math::radianCos(movementAngle) * getMaxMovementSpeed();
        float speedY = math::radianSin(movementAngle) * getMaxMovementSpeed();

        setCurrentSpeed(speedX, speedY);
    } else {
        setCurrentSpeed(0, 0);
    }
}

void Player::handleRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio) {
    defaultRender(resources, graphicContext, predictionRatio);
    defaultRenderHealth(graphicContext, Color{0, 0x77, 0, 0xFF}, 0);
}

void Player::selectNextWeapon() {
    auto last = mWeapons.size() - 1;
    if(mSelectedWeaponIdx < last) {
        mSelectedWeaponIdx++;
    } else {
        mSelectedWeaponIdx = static_cast<unsigned>(last);
    }
}

void Player::selectPreviousWeapon() {
    auto first = 0u;
    if(mSelectedWeaponIdx > first) {
        mSelectedWeaponIdx--;
    }
}

void Player::selectWeapon(unsigned idx) {
    auto last = mWeapons.size() - 1;
    if(idx <= last) {
        mSelectedWeaponIdx = idx;
    }
}

void Player::addWeapon(Weapon weapon) {
    mWeapons.emplace_back(weapon);
}

float Player::getCurrentSpeedX() const {
    return mCurrentSpeedX;
}

float Player::getCurrentSpeedY() const {
    return mCurrentSpeedY;
}

void Player::setCurrentSpeedX(float speedX) {
    mCurrentSpeedX = speedX;
}

void Player::setCurrentSpeedY(float speedY) {
    mCurrentSpeedY = speedY;
}

void Player::setCurrentSpeed(float speedX, float speedY) {
    setCurrentSpeedX(speedX);
    setCurrentSpeedY(speedY);
}
