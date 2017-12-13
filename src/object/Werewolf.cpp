#include "Werewolf.h"
#include "../shape/Circle.h"
#include "../shape/Box.h"
#include "../shape/Color.h"
#include "../math/math.h"
#include "../engine/GraphicContext.h"
#include "../engine/Random.h"
#include "../assets/Assets.h"
#include "../sdl/Sound.h"
#include <SDL_render.h>

using std::vector;

Werewolf::Werewolf(float x, float y)
        : _x{x}, _y{y} {
    _hp = Werewolf::defaultHp();

    _timer.restart();
    _teleportCd.restart();
}

// GameObject legacy
float Werewolf::getX() const { return _x; }

float Werewolf::getY() const { return _y; }

void Werewolf::setX(float x) { _x = x; }

void Werewolf::setY(float y) { _y = y; }

float Werewolf::getAngle() const { return _angle; }

float Werewolf::getSpeed() const { return _speed; }

void Werewolf::setAngle(float a) { _angle = a; }

void Werewolf::setSpeed(float s) { _speed = s; }

Circle Werewolf::getCircle() const { return {_x, _y, 25}; }

int Werewolf::hp() const { return _hp; }

int Werewolf::defaultHp() const { return 30; }

int Werewolf::dmg() const { if(_state == ATTACKING && (_frame == 3 || _frame == 7)) return 10; else return 0; }

std::string Werewolf::getTexName() const {
    std::string name = "wolf";

    if(_state == ATTACKING) {
        name += "_attack";
        name += std::to_string(_frame);
    } else if(_state == TELEPORTING) {
        name += "_teleport";
        name += std::to_string(_frame);
    } else if(_state == DYING) {
        name += "_teleport";
        name += std::to_string(_frame);
    } else {
        name += "_move";
        name += std::to_string(_frame);
    }

    return name;
}

void Werewolf::damage(int d) {
    if(_state == TELEPORTING) d /= 2;

    if(d > 0) _hp -= d;
    if(_hp <= 0 && _state != DYING) {
        _state = DYING;
        _frame = 0;
    }
}

void Werewolf::set_target(float x, float y, bool ignore) {
    if(ignore || _state == DYING) return;

    if(_state == TELEPORTING) {
        if(!_teleportCd.ticksHavePassed(500)) return;
    }

    _angle = toCartesian(::getAngle(_x, _y, x, y));

    auto dist = getDistance(_x, _y, x, y);
    if(dist > getCircle().getRadius() * 1.7f) {
        if(_state != MOVING) {
            _state = MOVING;
            _frame = 0;
        }
    } else if(_state != ATTACKING) {
        _state = ATTACKING;
        _frame = 0;
    }
}

void Werewolf::handle_logic() {
    if(_state == DYING) return;

    if(_state == MOVING) {
        default_move();
    } else if(_state == ATTACKING) {
        if(_timer.ticksHavePassed(600)) {
            _timer.restart();
            _state = MOVING;
            _frame = 0;
        }
    }
}

void Werewolf::teleport(Random& random) {
    if(_state == DYING) return;

    if(_state != TELEPORTING && _teleportCd.ticksHavePassed(1000)) {
        _x += random.getInt(-150, 150);
        _y += random.getInt(-150, 150);
        _state = TELEPORTING;
        _frame = 0;
        _teleportCd.restart();
    }
}

void Werewolf::handle_render(Assets& assets, GraphicContext& graphicContext) {
    default_render(assets, graphicContext);

    if(_hp > 0) {
        Box healthBox;
        healthBox.setSize(1.66f * _hp, 5);
        healthBox.setPosition(_x - healthBox.getWidth() / 2, _y - getCircle().getRadius());
        graphicContext.renderBox(healthBox, Color{0x55, 0, 0x33});
    }

    if(_state == ATTACKING) {
        if(_frame == 3 || _frame == 7) {
            assets.sound("wolf_attack").play();
        }

        if(_timer.ticksHavePassed(100)) {
            ++_frame;
            if(_frame >= 8) _frame = 0;
            _timer.restart();
        }
    } else if(_state == MOVING) {
        if(_timer.ticksHavePassed(100)) {
            ++_frame;
            if(_frame >= 6) _frame = 0;
            _timer.restart();
        }
    } else if(_state == TELEPORTING) {
        if(_timer.ticksHavePassed(100)) {
            if(_frame == 2) assets.sound("wolf_teleport").play();

            ++_frame;
            if(_frame > 2) _frame = 0;
            _timer.restart();
        }
    } else if(_state == DYING) {
        if(_frame < 2 && _timer.ticksHavePassed(500)) {
            ++_frame;
            _timer.restart();
        }
    }
}

bool Werewolf::dead() const {
    return _state == DYING && _frame == 2;
}

void Werewolf::setPos(float x, float y) {
    setX(x);
    setY(y);
}

vector<Werewolf>& werewolves() {
    static vector<Werewolf> ret;
    return ret;
}
