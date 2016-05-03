#include "GameObject.h"
#include "GameState.h"
#include "sdlwrap.h"
#include <SDL_events.h>
#include <SDL_render.h>

Player::Player(int x, int y)
: _x(x), _y(y)
{
}

float Player::x() const { return _x; }
float Player::y() const { return _y; }
float Player::angle() const { return _angle; }
float Player::speed() const { return _speed; }

void Player::x(float x) { _x = x; }
void Player::y(float y) { _y = y; }
void Player::angle(float a) { _angle = a; }
void Player::speed(float s) { _speed = s; }

std::string Player::texName() const { return _tex; }

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
}

void Player::handle_render() {
    default_render();
}
