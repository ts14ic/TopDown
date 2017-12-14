#include "Werewolf.h"
#include "../shape/Circle.h"
#include "../shape/Box.h"
#include "../shape/Color.h"
#include "../math/math.h"
#include "../engine/GraphicContext.h"
#include "../engine/Random.h"
#include "../resources/Resources.h"
#include "../resources/Sound.h"

using std::vector;

Werewolf::Werewolf(float x, float y)
        : _x{x}, _y{y} {
    _hp = Werewolf::defaultHp();
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

void Werewolf::damage(const Clock& clock, int d) {
    if(_state == TELEPORTING) d /= 2;

    if(d > 0) _hp -= d;
    if(_hp <= 0 && _state != DYING) {
        _state = DYING;
        _frame = 0;
    }
}

void Werewolf::set_target(const Clock& clock, float x, float y, bool ignore) {
    if(ignore || _state == DYING) return;

    if(_state == TELEPORTING) {
        if(!mTeleportCooldown.haveTicksPassedSinceStart(clock, 500)) return;
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

void Werewolf::handle_logic(const Clock& clock) {
    if(_state == DYING) return;

    if(_state == MOVING) {
        default_move();
    } else if(_state == ATTACKING) {
        if(mAttackCooldown.haveTicksPassedSinceStart(clock, 600)) {
            mAttackCooldown.restart(clock);
            _state = MOVING;
            _frame = 0;
        }
    }
}

void Werewolf::teleport(const Clock& clock, Random& random) {
    if(_state == DYING) return;

    if(_state != TELEPORTING && mTeleportCooldown.haveTicksPassedSinceStart(clock, 1000)) {
        _x += random.getInt(-150, 150);
        _y += random.getInt(-150, 150);
        _state = TELEPORTING;
        _frame = 0;
        mTeleportCooldown.restart(clock);
    }
}

void Werewolf::handle_render(Resources& resources, GraphicContext& graphicContext, AudioContext& audioContext) {
    default_render(resources, graphicContext);

    if(_hp > 0) {
        Box healthBox;
        healthBox.setSize(1.66f * _hp, 5);
        healthBox.setPosition(_x - healthBox.getWidth() / 2, _y - getCircle().getRadius());
        graphicContext.renderBox(healthBox, Color{0x55, 0, 0x33});
    }

    const auto& clock = resources.getClock();
    // todo Wow, wow, wow. Fix all the repetition
    if(_state == ATTACKING) {
        if(_frame == 3 || _frame == 7) {
            audioContext.playSound(resources.getSound("wolf_attack"));
        }

        if(mAttackCooldown.haveTicksPassedSinceStart(clock, 100)) {
            ++_frame;
            if(_frame >= 8) _frame = 0;
            mAttackCooldown.restart(clock);
        }
    } else if(_state == MOVING) {
        if(mAttackCooldown.haveTicksPassedSinceStart(clock, 100)) {
            ++_frame;
            if(_frame >= 6) _frame = 0;
            mAttackCooldown.restart(clock);
        }
    } else if(_state == TELEPORTING) {
        if(mAttackCooldown.haveTicksPassedSinceStart(clock, 100)) {
            if(_frame == 2) {
                audioContext.playSound(resources.getSound("wolf_teleport"));
            }

            ++_frame;
            if(_frame > 2) _frame = 0;
            mAttackCooldown.restart(clock);
        }
    } else if(_state == DYING) {
        if(_frame < 2 && mAttackCooldown.haveTicksPassedSinceStart(clock, 500)) {
            ++_frame;
            mAttackCooldown.restart(clock);
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
