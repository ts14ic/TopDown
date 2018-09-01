#include "Werewolf.h"
#include "math/maths.h"

using std::vector;

Werewolf::Werewolf(float x, float y)
        : _position(x, y) {
    _current_hp = Werewolf::get_default_hp();
}

float Werewolf::get_angle() const { return _view_angle; }

float Werewolf::get_max_movement_speed() const { return _max_movement_speed; }

void Werewolf::set_angle(float a) { _view_angle = a; }

void Werewolf::set_max_movement_speed(float s) { _max_movement_speed = s; }

Circle Werewolf::get_circle() const { return {_position, 25}; }

int Werewolf::get_hp() const { return _current_hp; }

int Werewolf::get_default_hp() const { return 30; }

int Werewolf::get_damage() const {
    if (_ai_state == ATTACKING && (_animation_frame == 3 || _animation_frame == 7))
        return 10;
    else return 0;
}

std::string Werewolf::get_tex_name() const {
    std::string name = "wolf";

    if (_ai_state == ATTACKING) {
        name += "_attack";
        name += std::to_string(_animation_frame);
    } else if (_ai_state == TELEPORTING) {
        name += "_teleport";
        name += std::to_string(_animation_frame);
    } else if (_ai_state == DYING) {
        name += "_teleport";
        name += std::to_string(_animation_frame);
    } else {
        name += "_move";
        name += std::to_string(_animation_frame);
    }

    return name;
}

void Werewolf::damage(const Clock& clock, int d) {
    if (_ai_state == TELEPORTING) d /= 2;

    if (d > 0) _current_hp -= d;
    if (_current_hp <= 0 && _ai_state != DYING) {
        _ai_state = DYING;
        _animation_frame = 0;
    }
}

void Werewolf::set_target(const Clock& clock, Point2<float> position) {
    if (_ai_state == DYING) return;

    if (_ai_state == TELEPORTING
        && !_teleport_cooldown.ticks_passed_since_start(clock, 500)) {
        return;
    }

    set_angle(math::get_cartesian_angle(_position.x, _position.y, position.x, position.y));

    auto dist = math::get_distance(_position.x, _position.y, position.x, position.y);
    if (dist > get_circle().get_radius() * 1.7f) {
        if (_ai_state != MOVING) {
            _ai_state = MOVING;
            _animation_frame = 0;
        }
    } else if (_ai_state != ATTACKING) {
        _ai_state = ATTACKING;
        _animation_frame = 0;
    }
}

void Werewolf::handle_logic(const Clock& clock) {
    if (_ai_state == DYING) {
        set_current_speed(0, 0);
        return;
    }

    if (_ai_state == MOVING) {
        // TODO extract speed setting
        auto movement_angle = get_angle();

        float x_speed = math::cartesian_cos(movement_angle) * get_max_movement_speed();
        float y_speed = math::cartesian_sin(movement_angle) * get_max_movement_speed();

        set_current_speed(x_speed, y_speed);
        default_move();
    } else {
        set_current_speed(0.f, 0.f);
    }

    if (_ai_state == ATTACKING && _attack_cooldown.ticks_passed_since_start(clock, 600)) {
        _attack_cooldown.restart(clock);
        _ai_state = MOVING;
        _animation_frame = 0;
    }
}

void Werewolf::teleport(const Clock& clock, Random& random) {
    if (_ai_state == DYING) return;

    if (_ai_state != TELEPORTING && _teleport_cooldown.ticks_passed_since_start(clock, 1000)) {
        _position.x += random.get_int(-150, 150);
        _position.y += random.get_int(-150, 150);
        _ai_state = TELEPORTING;
        _animation_frame = 0;
        _teleport_cooldown.restart(clock);
    }
}

void Werewolf::handle_render(Engine& engine, Graphic& graphic_context, Audio& audio,
                             float frames_count) {
    default_render(graphic_context, frames_count);

    if (_current_hp > 0) {
        Box health_box;
        health_box.set_sizes(1.66f * _current_hp, 5);
        health_box.set_left_top(
                _position.x - health_box.get_width() / 2,
                _position.y - get_circle().get_radius()
        );
        graphic_context.render_box(health_box, Color{0x55, 0, 0x33});
    }

    const auto& clock = engine.get_clock();
    // TODO Wow, wow, wow. Fix all the repetition
    if (_ai_state == ATTACKING) {
        if (_animation_frame == 3 || _animation_frame == 7) {
            audio.play_sound("wolf_attack");
        }

        if (_attack_cooldown.ticks_passed_since_start(clock, 100)) {
            ++_animation_frame;
            if (_animation_frame >= 8) _animation_frame = 0;
            _attack_cooldown.restart(clock);
        }
    } else if (_ai_state == MOVING) {
        if (_attack_cooldown.ticks_passed_since_start(clock, 100)) {
            ++_animation_frame;
            if (_animation_frame >= 6) _animation_frame = 0;
            _attack_cooldown.restart(clock);
        }
    } else if (_ai_state == TELEPORTING) {
        if (_attack_cooldown.ticks_passed_since_start(clock, 100)) {
            if (_animation_frame == 2) {
                audio.play_sound("wolf_teleport");
            }

            ++_animation_frame;
            if (_animation_frame > 2) _animation_frame = 0;
            _attack_cooldown.restart(clock);
        }
    } else if (_ai_state == DYING) {
        if (_animation_frame < 2 && _attack_cooldown.ticks_passed_since_start(clock, 500)) {
            ++_animation_frame;
            _attack_cooldown.restart(clock);
        }
    }
}

bool Werewolf::is_dead() const {
    return _ai_state == DYING && _animation_frame == 2;
}

float Werewolf::get_current_x_speed() const {
    return _current_x_speed;
}

float Werewolf::get_current_y_speed() const {
    return _current_y_speed;
}

void Werewolf::set_current_x_speed(float x_speed) {
    _current_x_speed = x_speed;
}

void Werewolf::set_current_y_speed(float y_speed) {
    _current_y_speed = y_speed;
}

void Werewolf::set_current_speed(float x_speed, float y_speed) {
    set_current_x_speed(x_speed);
    set_current_y_speed(y_speed);
}

vector<Werewolf>& werewolves() {
    static vector<Werewolf> ret;
    return ret;
}
