#include "Player.h"
#include "../shape/Circle.h"
#include "../shape/Color.h"
#include "../math/math.h"
#include "../resources/Resources.h"
#include "../event/KeyboardEvent.h"
#include "../event/MouseEvent.h"
#include <sstream>
#include <iostream>

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

float Player::getSpeed() const { return _speed; }

void Player::setX(float x) { mX = x; }

void Player::setY(float y) { mY = y; }

void Player::setAngle(float a) { mAngle = a; }

void Player::setSpeed(float s) { _speed = s; }

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
            mAngle = toCartesian(::getAngle(getX(), getY(), event.getX(), event.getY()));
            mMouseX = event.getX();
            mMouseY = event.getY();
            break;
        }
    }
}

void Player::handle_logic(Random& random, Resources& resources, AudioContext& audioContext) {
//    int mx, my;
//    SDL_GetMouseState(&mx, &my);
//    mAngle = toCartesian(::getAngle(mX, mY, mx, my));

    if(mDamageCooldown.haveTicksPassedSinceStart(resources.getClock(), 500)) {
        _speed = 2.3f;
    } else {
        _speed = 1.0f;
    }

    if(mInputState.test(DOWN_PRESSED)) {
        mY = mY + _speed;
    }
    if(mInputState.test(UP_PRESSED)) {
        mY = mY - _speed;
    }
    if(mInputState.test(LEFT_PRESSED)) {
        mX = mX - _speed;
    }
    if(mInputState.test(RIGHT_PRESSED)) {
        mX = mX + _speed;
    }

    if(!mWeapons.empty()) {
        // todo don't try to reload on every frame
        mWeapons[mSelectedWeaponIdx].tryReload(resources.getClock());
        if(mInputState.test(TRIGGER_PRESSED)) {
            mWeapons[mSelectedWeaponIdx].pullTrigger(random, resources, audioContext, *this);
        }
    }
}

void Player::handle_render(Resources& resources, GraphicContext& graphicContext) {
    default_render(resources, graphicContext);
    default_render_health(graphicContext, Color{0, 0x77, 0, 0xFF});
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
