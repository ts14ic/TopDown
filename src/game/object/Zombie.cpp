#include "Zombie.h"
#include "math/maths.h"

using std::vector;

Zombie::Zombie(int x, int y)
        : _x(x), _y(y) {
    _current_hp = Zombie::get_default_hp();
}

float Zombie::get_x() const { return _x; }

float Zombie::get_y() const { return _y; }

void Zombie::set_x(float x) { _x = x; }

void Zombie::set_y(float y) { _y = y; }

float Zombie::get_angle() const { return _angle; }

float Zombie::get_max_movement_speed() const { return _speed; }

void Zombie::set_angle(float a) { _angle = a; }

void Zombie::set_max_movement_speed(float s) { _speed = s; }

Circle Zombie::get_circle() const { return {_x, _y, 25}; }

int Zombie::get_hp() const { return _current_hp; }

int Zombie::get_default_hp() const { return 50; }

int Zombie::get_damage() const { if(_ai_state == ATTACKING && _animation_frame == 5) return 15; else return 0; }

std::string Zombie::get_tex_name() const {
    std::string name = "zombie";

    if(_ai_state == ATTACKING) {
        name += "_attack";
        name += std::to_string(_animation_frame);
    } else if(_ai_state == DYING) {
        name += "_death";
        name += std::to_string(_animation_frame);
    }

    return name;
}

void Zombie::damage(const Clock &clock, int d) {
    if(d > 0) _current_hp -= d;

    if(_current_hp <= 0 && _ai_state != DYING) {
        _ai_state = DYING;
        _animation_frame = 0;
    }
}

void Zombie::set_target(float x, float y) {
    if(_ai_state == DYING) return;

    _angle = math::get_cartesian_angle(_x, _y, x, y);

    auto dist = math::get_distance(_x, _y, x, y);
    if(dist > get_circle().get_radius() * 1.7f) {
        if(_ai_state != MOVING) {
            _ai_state = MOVING;
            _animation_frame = 0;
        }
    } else if(_ai_state != ATTACKING) {
        _ai_state = ATTACKING;
        _animation_frame = 0;
    }
}

void Zombie::handle_logic() {
    if(_ai_state == DYING) {
        set_current_speed(0, 0);
        return;
    }

    if(_ai_state == MOVING) {
        // TODO extract speed setting
        auto movementAngle = get_angle();

        float speedX = math::cartesian_cos(movementAngle) * get_max_movement_speed();
        float speedY = math::cartesian_sin(movementAngle) * get_max_movement_speed();

        set_current_speed(speedX, speedY);
        default_move();
    } else {
        set_current_speed(0.f, 0.f);
    }
}

void Zombie::handle_render(Engine &engine, Graphic &graphic, Audio &audio,
                           float predictionRatio) {
    default_render(graphic, predictionRatio);
    default_render_health(graphic, Color{0, 0x77, 0, 0xFF}, 0);

    const auto& clock = engine.get_clock();
    if(_ai_state == ATTACKING) {
        if(_animation_frame == 5) {
            audio.play_sound(audio.get_sound("zombie_attack"));
        }

        if(_animation_timer.ticks_passed_since_start(clock, 100)) {
            ++_animation_frame;
            if(_animation_frame >= 6) _animation_frame = 0;
            _animation_timer.restart(clock);
        }
    } else if(_ai_state == DYING) {
        if(_animation_frame < 7 && _animation_timer.ticks_passed_since_start(clock, 500)) {
            ++_animation_frame;
            _animation_timer.restart(clock);
        }
    }
}

bool Zombie::is_dead() const {
    return _ai_state == DYING && _animation_frame == 7;
}

void Zombie::set_position(float x, float y) {
    set_x(x);
    set_y(y);
}

float Zombie::get_current_speed_x() const {
    return _current_speed_x;
}

float Zombie::get_current_speed_y() const {
    return _current_speed_y;
}

void Zombie::set_current_speed_x(float speedX) {
    _current_speed_x = speedX;
}

void Zombie::set_current_speed_y(float speedY) {
    _current_speed_y = speedY;
}

void Zombie::set_current_speed(float speedX, float speedY) {
    set_current_speed_x(speedX);
    set_current_speed_y(speedY);
}

vector<Zombie>& zombies() {
    static vector<Zombie> ret;
    return ret;
}
