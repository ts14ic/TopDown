#include "Player.h"
#include <engine/geometry/maths.h>
#include <sstream>
#include <cmath>

Player::Player()
        : Player{make_point<float>(0, 0)} {}

Player::Player(Point2<float> position)
        : _transform{Transform{position, 0.0f, 30.0f}},
          _hitpoints{Hitpoints{100}} {}

std::string Player::get_tex_name() const {
    if (_weapons.any_selected()) {
        std::ostringstream stream;
        stream << "player_" << _weapons.get_selected_name();
        return stream.str();
    } else {
        return "player";
    }
}

int Player::get_damage() const { return 0; }

bool Player::is_dead() const {
    return !has_hp();
}

void Player::take_damage(const Clock& clock, int damageAmount) {
    if (damageAmount > 0 && _damage_cooldown.ticks_passed_since_start(clock, 500)) {
        _hitpoints.current_hp -= damageAmount;
        _damage_cooldown.restart(clock);
    }
}

bool Player::reloading() const {
    return _weapons.is_selected_reloading();
}

void Player::handle_key_event(const KeyboardEvent& event) {
    if (event.get_type() == KeyboardEvent::Type::KEY_DOWN) {
        switch (event.get_key()) {
            case KEY_UP:
            case 'w': {
                _input_state.set(INPUT_UP_PRESSED);
                break;
            }

            case KEY_DOWN:
            case 's': {
                _input_state.set(INPUT_DOWN_PRESSED);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                _input_state.set(INPUT_LEFT_PRESSED);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                _input_state.set(INPUT_RIGHT_PRESSED);
                break;
            }

            case KEY_SPACE: {
                _input_state.set(INPUT_TRIGGER_PRESSED);
                break;
            }

            default: {
                break;
            }
        }
    } else if (event.get_type() == KeyboardEvent::Type::KEY_UP) {
        switch (event.get_key()) {
            case KEY_UP:
            case 'w': {
                _input_state.reset(INPUT_UP_PRESSED);
                break;
            }

            case KEY_DOWN:
            case 's': {
                _input_state.reset(INPUT_DOWN_PRESSED);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                _input_state.reset(INPUT_LEFT_PRESSED);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                _input_state.reset(INPUT_RIGHT_PRESSED);
                break;
            }

            case KEY_SPACE: {
                _input_state.reset(INPUT_TRIGGER_PRESSED);
                break;
            }

            default: {
                int key = event.get_key();
                if (key >= '0' && key <= '9') {
                    auto index = 9U - ('9' - key);
                    _weapons.select_by_index(index);
                }
                break;
            }
        }
    }
}


void Player::handle_mouse_event(const MouseScrollEvent& event) {
    switch (event.get_type()) {
        case MouseScrollEvent::Type::SCROLL_UP: {
            _weapons.select_previous();
            break;
        }

        case MouseScrollEvent::Type::SCROLL_DOWN: {
            _weapons.select_next();
            break;
        }
    }
}

void Player::handle_mouse_event(const MousePointEvent& event) {
    switch (event.get_type()) {
        case MousePointEvent::Type::MOTION: {
            _transform.angle = math::get_cartesian_angle(_transform.position, event.get_position());
            break;
        }

        case MousePointEvent::Type::BUTTON_UP: {
            _input_state.reset(INPUT_TRIGGER_PRESSED);
            break;
        }

        case MousePointEvent::Type::BUTTON_DOWN: {
            _input_state.set(INPUT_TRIGGER_PRESSED);
            break;
        }
    }
}

void Player::handle_logic(Random& random, Engine& engine, Audio& audio) {
    // TODO Make the timer store a pointer to clock
    // TODO AFTER Move the condition inside the getter
    set_max_movement_speed(_damage_cooldown.ticks_passed_since_start(engine.get_clock(), 500) ? 2.3f : 1.0f);

    update_speeds();

    default_move();

    // TODO don't try to reload on every frame
    _weapons.try_reload_selected(engine.get_clock());

    if (_input_state.test(INPUT_TRIGGER_PRESSED)) {
        _weapons.pull_trigger(engine, *this);
    }
}

void Player::update_speeds() {
    // TODO extract speed calculations to share between classes
    int direction_x = _input_state.test(INPUT_RIGHT_PRESSED) - _input_state.test(INPUT_LEFT_PRESSED);
    int direction_y = _input_state.test(INPUT_DOWN_PRESSED) - _input_state.test(INPUT_UP_PRESSED);

    if (direction_x != 0 || direction_y != 0) {
        auto movement_angle = math::get_radian_angle(make_point(0, 0), make_point(direction_x, direction_y));

        set_current_speed(
                math::radian_cos(movement_angle) * get_max_movement_speed(),
                math::radian_sin(movement_angle) * get_max_movement_speed()
        );
    } else {
        set_current_speed(0.f, 0.f);
    }
}

void Player::handle_render(Engine& engine, Graphic& graphic, float frames_count) {
    default_render(graphic, frames_count);
    default_render_health(graphic, Color{0, 0x77, 0, 0xFF}, 0);
}

void Player::add_weapon(Weapon weapon) {
    _weapons.add(weapon);
}
