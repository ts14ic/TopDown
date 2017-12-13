#include "Player.h"
#include "../shape/Circle.h"
#include "../shape/Color.h"
#include "../math/math.h"
#include "../engine/InputContext.h"
#include <SDL_events.h>
#include <sstream>
#include <iostream>

Player::Player()
        : Player(0, 0) {}

Player::Player(int x, int y)
        : mX(x), mY(y) {
    _hp = Player::defaultHp();

    _dmgCd.restart();
}

void Player::setPos(float x, float y) {
    mX = x;
    mY = y;
}

float Player::getX() const { return mX; }

float Player::getY() const { return mY; }

float Player::getAngle() const { return _angle; }

float Player::getSpeed() const { return _speed; }

void Player::setX(float x) { mX = x; }

void Player::setY(float y) { mY = y; }

void Player::setAngle(float a) { _angle = a; }

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

void Player::damage(int v) {
    if(v > 0 && _dmgCd.ticksHavePassed(500)) {
        _hp -= v;
        _dmgCd.restart();
    }
}

bool Player::reloading() const {
    return !mWeapons.empty() && mWeapons[mSelectedWeaponIdx].isReloading();
}

void Player::handle_events(InputContext& input) {
    switch(input.getInputEvent().type) {
        case SDL_MOUSEWHEEL:
            if(input.getInputEvent().wheel.y < 0) {
                selectNextWeapon();
            } else {
                selectPreviousWeapon();
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(input.getInputEvent().button.button == SDL_BUTTON_LEFT) {
                mInputState.set(TRIGGER_PRESSED);
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if(input.getInputEvent().button.button == SDL_BUTTON_LEFT) {
                mInputState.reset(TRIGGER_PRESSED);
            }
            break;

        case SDL_KEYDOWN:
            switch(input.getInputEvent().key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w: {
                    mInputState.set(UP_PRESSED);
                    break;
                }

                case SDLK_DOWN:
                case SDLK_s: {
                    mInputState.set(DOWN_PRESSED);
                    break;
                }

                case SDLK_LEFT:
                case SDLK_a: {
                    mInputState.set(LEFT_PRESSED);
                    break;
                }

                case SDLK_RIGHT:
                case SDLK_d: {
                    mInputState.set(RIGHT_PRESSED);
                    break;
                }

                case SDLK_SPACE: {
                    mInputState.set(TRIGGER_PRESSED);
                    break;
                }

                default:;
            }
            break;

        case SDL_KEYUP:
            switch(input.getInputEvent().key.keysym.sym) {
                case SDLK_0:
                case SDLK_1:
                case SDLK_2:
                case SDLK_3:
                case SDLK_4:
                case SDLK_5:
                case SDLK_6:
                case SDLK_7:
                case SDLK_8:
                case SDLK_9: {
                    auto keysym = input.getInputEvent().key.keysym.sym;
                    auto idx = 9u - (SDLK_9 - keysym);
                    selectWeapon(idx);
                    break;
                }

                case SDLK_UP:
                case SDLK_w: {
                    mInputState.reset(UP_PRESSED);
                    break;
                }

                case SDLK_DOWN:
                case SDLK_s: {
                    mInputState.reset(DOWN_PRESSED);
                    break;
                }

                case SDLK_LEFT:
                case SDLK_a: {
                    mInputState.reset(LEFT_PRESSED);
                    break;
                }

                case SDLK_RIGHT:
                case SDLK_d: {
                    mInputState.reset(RIGHT_PRESSED);
                    break;
                }

                case SDLK_SPACE: {
                    mInputState.reset(TRIGGER_PRESSED);
                    break;
                }

                default:;
            }
            break;

        case SDL_MOUSEMOTION:
            _angle = toCartesian(
                    ::getAngle(getX(), getY(), input.getInputEvent().motion.x, input.getInputEvent().motion.y));
            break;

        default:;
    }
}

void Player::handle_logic(Random& random, Assets& assets) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    _angle = toCartesian(::getAngle(mX, mY, mx, my));

    if(_dmgCd.ticksHavePassed(500)) {
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
        mWeapons[mSelectedWeaponIdx].tryReload();
        if(mInputState.test(TRIGGER_PRESSED)) {
            mWeapons[mSelectedWeaponIdx].pullTrigger(random, assets, *this);
        }
    }
}

void Player::handle_render(Assets& assets, RenderContext& renderContext) {
    default_render(assets, renderContext);
    default_render_health(renderContext, Color{0, 0x77, 0, 0xFF});
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
