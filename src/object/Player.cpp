#include <sstream>
#include "Player.h"
#include "../shape/Circle.h"
#include "../math/math.h"
#include "../engine/InputContext.h"
#include "WeaponBuilder.h"

Player::Player()
        : Player(0, 0) {}

Player::Player(int x, int y)
        : mX(x), mY(y) {
    _hp = Player::defaultHp();

    mWeapons.emplace_back(WeaponBuilder{"pistol"}
                                  .maxAmmo(7)
                                  .projectilesPerShot(1)
                                  .length(10)
                                  .projectileDamage(15)
                                  .projectileSpeed(12)
                                  .fireCooldown(350)
                                  .reloadCooldown(1000)
                                  .projectileSpread(2)
                                  .fireSounds({"pistol_shot"})
                                  .build());
    mWeapons.emplace_back(WeaponBuilder{"shotgun"}
                                  .maxAmmo(2)
                                  .projectilesPerShot(8)
                                  .length(45)
                                  .projectileDamage(7)
                                  .projectileSpeed(8)
                                  .fireCooldown(200)
                                  .reloadCooldown(1000)
                                  .projectileSpread(20)
                                  .fireSounds({"shotgun_shot"})
                                  .build());
    mWeapons.emplace_back(WeaponBuilder{"uzi"}
                                  .maxAmmo(25)
                                  .projectilesPerShot(1)
                                  .length(25)
                                  .projectileDamage(10)
                                  .projectileSpeed(12)
                                  .fireCooldown(100)
                                  .reloadCooldown(3000)
                                  .projectileSpread(5)
                                  .fireSounds({"uzi_shot1", "uzi_shot2"})
                                  .build());

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
    std::ostringstream ostringstream;
    ostringstream << "player_" << mWeapons[mSelectedWeaponIdx].getName();
    return ostringstream.str();
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
    return mWeapons[mSelectedWeaponIdx].isReloading();
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
                case SDLK_1:
                    mSelectedWeaponIdx = 0;
                    break;

                case SDLK_2:
                    mSelectedWeaponIdx = 1;
                    break;

                case SDLK_3:
                    mSelectedWeaponIdx = 2;
                    break;

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

void Player::handle_logic(Assets& assets) {
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

    mWeapons[mSelectedWeaponIdx].tryReload();
    if(mInputState.test(TRIGGER_PRESSED)) {
        mWeapons[mSelectedWeaponIdx].pullTrigger(assets, *this);
    }
}

void Player::handle_render(Assets& assets, RenderContext& renderContext) {
    default_render(assets, renderContext);
    default_render_health(renderContext, SDL_Color{0, 0x77, 0, 0xFF});
}

void Player::selectNextWeapon() {
    selectWeapon(mSelectedWeaponIdx + 1);
}

void Player::selectPreviousWeapon() {
    selectWeapon(mSelectedWeaponIdx - 1);
}

void Player::selectWeapon(int idx) {
    mSelectedWeaponIdx = idx;
    if(mSelectedWeaponIdx < 0) {
        mSelectedWeaponIdx = static_cast<int>(0);
    } else if(mSelectedWeaponIdx > mWeapons.size() - 1) {
        mSelectedWeaponIdx = static_cast<int>(mWeapons.size() - 1);
    }
}
