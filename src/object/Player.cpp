#include "Player.h"
#include "../utils/Circle.h"
#include "../utils/calculations.h"
#include "../engine/InputContext.h"
#include "WeaponV2.h"
#include "WeaponBuilder.h"

Player::Player(int x, int y)
        : _x(x), _y(y) {
    _hp = Player::defaultHp();

    mWeapons[WEAPON_PISTOL] = std::make_unique<WeaponV2>(WeaponBuilder{}
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
    mWeapons[WEAPON_SHOTGUN] = std::make_unique<WeaponV2>(WeaponBuilder{}
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
    mWeapons[WEAPON_UZI] = std::make_unique<WeaponV2>(WeaponBuilder{}
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

    _dmgCd.start();
}

float Player::x() const { return _x; }

float Player::y() const { return _y; }

float Player::angle() const { return _angle; }

float Player::speed() const { return _speed; }

void Player::x(float x) { _x = x; }

void Player::y(float y) { _y = y; }

void Player::angle(float a) { _angle = a; }

void Player::speed(float s) { _speed = s; }

Circle Player::circle() const { return Circle(_x, _y, 30); }

std::string Player::texName() const {
    std::string name = "player";

    switch(_currentWeap) {
        case WEAPON_SHOTGUN:
            return name += "_shotgun";

        case WEAPON_UZI:
            return name += "_uzi";

        default:
            return name += "_pistol";
    }
}

int Player::hp() const { return _hp; }

int Player::defaultHp() const { return 100; }

int Player::dmg() const { return 0; }

bool Player::dead() const {
    return _hp <= 0;
}

void Player::damage(int v) {
    if(v > 0 && _dmgCd.passed(500)) {
        _hp -= v;
        _dmgCd.start();
    }
}

bool Player::reloading() const {
    return mWeapons[_currentWeap]->reloading();
}

void Player::handle_events(InputContext& input) {
    switch(input.getInputEvent().type) {
        case SDL_MOUSEWHEEL:
            if(input.getInputEvent().wheel.y < 0) {
                if(_currentWeap < WEAPON_LAST) ++_currentWeap;
            } else {
                if(_currentWeap > WEAPON_FIRST) --_currentWeap;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(input.getInputEvent().button.button == SDL_BUTTON_LEFT) {
                _state |= SHOOTS;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if(input.getInputEvent().button.button == SDL_BUTTON_LEFT) {
                _state ^= SHOOTS;
            }
            break;

        case SDL_KEYDOWN:
            switch(input.getInputEvent().key.keysym.sym) {
                case SDLK_w:
                    _state |= MOVES_UP;
                    break;

                case SDLK_s:
                    _state |= MOVES_DOWN;
                    break;

                case SDLK_a:
                    _state |= MOVES_LEFT;
                    break;

                case SDLK_d:
                    _state |= MOVES_RIGHT;
                    break;

                case SDLK_SPACE:
                    _state |= SHOOTS;
                    break;

                default:;
            }
            break;

        case SDL_KEYUP:
            switch(input.getInputEvent().key.keysym.sym) {
                case SDLK_1:
                    _currentWeap = WEAPON_PISTOL;
                    break;

                case SDLK_2:
                    _currentWeap = WEAPON_SHOTGUN;
                    break;

                case SDLK_3:
                    _currentWeap = WEAPON_UZI;
                    break;

                case SDLK_w:
                    _state ^= MOVES_UP;
                    break;

                case SDLK_s:
                    _state ^= MOVES_DOWN;
                    break;

                case SDLK_a:
                    _state ^= MOVES_LEFT;
                    break;

                case SDLK_d:
                    _state ^= MOVES_RIGHT;
                    break;

                case SDLK_SPACE:
                    _state ^= SHOOTS;
                    break;

                default:;
            }
            break;

        case SDL_MOUSEMOTION:
            _angle = to_deg(get_angle(x(), y(), input.getInputEvent().motion.x, input.getInputEvent().motion.y));
            break;

        default:;
    }
}

void Player::handle_logic(Assets& assets) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    _angle = to_deg(get_angle(_x, _y, mx, my));

    if(_dmgCd.passed(500)) {
        _speed = 2.3f;
    } else {
        _speed = 1.0f;
    }

    if(_state & MOVES_DOWN) {
        _y = _y + _speed;
    }
    if(_state & MOVES_UP) {
        _y = _y - _speed;
    }
    if(_state & MOVES_LEFT) {
        _x = _x - _speed;
    }
    if(_state & MOVES_RIGHT) {
        _x = _x + _speed;
    }

    mWeapons[_currentWeap]->reload();
    if(_state & SHOOTS) {
        mWeapons[_currentWeap]->shoot(assets, *this);
    }
}

void Player::handle_render(Assets& assets, RenderContext& renderContext) {
    default_render(assets, renderContext);
    default_render_health(renderContext, SDL_Color{0, 0x77, 0, 0xFF});
}
