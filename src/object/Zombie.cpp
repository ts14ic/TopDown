#include "Zombie.h"
#include "../utils/Circle.h"
#include "../utils/calculations.h"
#include "../assets/Assets.h"
#include <SDL_pixels.h>

using std::vector;

Zombie::Zombie(int x, int y)
: _x(x), _y(y)
{
    _hp = Zombie::defaultHp();
}

float Zombie::x() const { return _x; }
float Zombie::y() const { return _y; }
void  Zombie::x(float x) { _x = x; }
void  Zombie::y(float y) { _y = y; }

float Zombie::angle() const { return _angle; }
float Zombie::speed() const { return _speed; }
void  Zombie::angle(float a) { _angle = a; }
void  Zombie::speed(float s) { _speed = s; }

Circle Zombie::circle() const { return Circle(_x, _y, 25); }

int Zombie::hp() const { return _hp; }
int Zombie::defaultHp() const { return 50; }
int Zombie::dmg() const { if(_state == ATTACKING && _frame == 5) return 15; else return 0; }

std::string Zombie::texName() const {
    std::string name = "zombie";

    if(_state == ATTACKING) {
        name += "_attack";
        name += std::to_string(_frame);
    } else if(_state == DYING) {
        name += "_death";
        name += std::to_string(_frame);
    }

    return name;
}

void Zombie::damage(int d) {
    if(d > 0) _hp -= d;

    if(_hp <= 0 && _state != DYING) {
        _state = DYING;
        _frame = 0;
    }
}

void Zombie::set_target(float x, float y, bool ignore) {
    if(ignore || _state == DYING) return;

    _angle = to_deg(get_angle(_x, _y, x, y));

    auto dist = get_distance(_x, _y, x, y);
    if(dist > circle().getRadius() * 1.7f) {
        if(_state != MOVING) {
            _state = MOVING;
            _frame = 0;
        }
    } else if(_state != ATTACKING) {
        _state = ATTACKING;
        _frame = 0;
    }
}

void Zombie::handle_logic() {
    if(_state == DYING) return;

    if(_state == MOVING) {
        default_move();
    }
}

void Zombie::handle_render(Assets& assets, RenderContext& renderContext) {
    default_render(assets, renderContext);
    default_render_health(renderContext, SDL_Color{0, 0x77, 0, 0xFF});

    if(_state == ATTACKING) {
        if(_frame == 5) {
            assets.sound("zombie_attack").play();
        }

        if(_timer.passed(100)) {
            ++_frame;
            if(_frame >= 6) _frame = 0;
            _timer.start();
        }
    } else if(_state == DYING) {
        if(_frame < 7 && _timer.passed(500)) {
            ++_frame;
            _timer.start();
        }
    }
}

bool Zombie::dead() const {
    return _state == DYING && _frame == 7;
}

vector<Zombie>& zombies() {
    static vector<Zombie> ret;
    return ret;
}
