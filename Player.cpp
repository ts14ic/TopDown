#include "GameObject.h"
#include "GameState.h"
#include "sdlwrap.h"
#include <SDL_events.h>
#include <SDL_render.h>

Player::Player(int x, int y)
: _x(x), _y(y)
{
    _hp = Player::defaultHp();
    
    _weapons[WEAPON_PISTOL].reset(new Pistol());
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

std::string Player::texName() const { return _tex; }

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

void Player::handle_events() {
    switch(gameEvent().type) {
        case SDL_KEYDOWN:
        switch(gameEvent().key.keysym.sym) {
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
        switch(gameEvent().key.keysym.sym) {
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
        _angle = to_deg(get_angle(x(), y(), gameEvent().motion.x, gameEvent().motion.y));
        break;
        
        default:;
    }
}

void Player::handle_logic() {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    _angle = to_deg(get_angle(_x, _y, mx, my));
    
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
    
    if(_state & SHOOTS) {
        _weapons[_currentWeap]->shoot(*this);
    }
}

void Player::handle_render() {
    default_render();
    default_render_health(SDL_Color{0, 0x77, 0, 0xFF});
}
