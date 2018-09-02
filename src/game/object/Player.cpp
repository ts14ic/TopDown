#include "Player.h"
#include <engine/geometry/maths.h>
#include <sstream>
#include <cmath>

Player::Player()
        : Player{make_point<float>(0, 0)} {}

Player::Player(Point2<float> position)
        : _position{position} {
    _hp = Player::get_default_hp();
}

float Player::get_angle() const { return _angle; }

float Player::get_max_movement_speed() const {
    return _max_movement_speed;
}

void Player::set_angle(float a) { _angle = a; }

void Player::set_max_movement_speed(float movementSpeed) {
    if (movementSpeed >= 0) {
        _max_movement_speed = movementSpeed;
    }
}

Circle Player::get_circle() const { return {_position, 30}; }

std::string Player::get_tex_name() const {
    if (_weapons.empty() || _selected_weapon_index >= _weapons.size()) {
        return "player";
    } else {
        std::ostringstream stream;
        stream << "player_" << _weapons[_selected_weapon_index].get_name();
        return stream.str();
    }
}

int Player::get_hp() const { return _hp; }

int Player::get_default_hp() const { return 100; }

int Player::get_damage() const { return 0; }

bool Player::is_dead() const {
    return _hp <= 0;
}

void Player::damage(const Clock& clock, int damageAmount) {
    if (damageAmount > 0 && _damage_cooldown.ticks_passed_since_start(clock, 500)) {
        _hp -= damageAmount;
        _damage_cooldown.restart(clock);
    }
}

bool Player::reloading() const {
    return !_weapons.empty() && _weapons[_selected_weapon_index].is_reloading();
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
                    auto idx = 9U - ('9' - key);
                    select_weapon(idx);
                }
                break;
            }
        }
    }
}


void Player::handle_mouse_event(const MouseScrollEvent& event) {
    switch (event.get_type()) {
        case MouseScrollEvent::Type::SCROLL_UP: {
            select_previous_weapon();
            break;
        }

        case MouseScrollEvent::Type::SCROLL_DOWN: {
            select_next_weapon();
            break;
        }
    }
}

void Player::handle_mouse_event(const MousePointEvent& event) {
    switch (event.get_type()) {
        case MousePointEvent::Type::MOTION: {
            _angle = math::get_cartesian_angle(_position, event.get_position());
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

    if (!_weapons.empty()) {
        // TODO don't try to reload on every frame
        _weapons[_selected_weapon_index].try_reload(engine.get_clock());
        if (_input_state.test(INPUT_TRIGGER_PRESSED)) {
            _weapons[_selected_weapon_index].pull_trigger(random, engine, audio, *this);
        }
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

void Player::select_next_weapon() {
    auto last = _weapons.size() - 1;
    if (_selected_weapon_index < last) {
        _selected_weapon_index++;
    } else {
        _selected_weapon_index = static_cast<unsigned>(last);
    }
}

void Player::select_previous_weapon() {
    auto first = 0u;
    if (_selected_weapon_index > first) {
        _selected_weapon_index--;
    }
}

void Player::select_weapon(unsigned index) {
    auto last = _weapons.size() - 1;
    if (index <= last) {
        _selected_weapon_index = index;
    }
}

void Player::addWeapon(Weapon weapon) {
    _weapons.emplace_back(weapon);
}
