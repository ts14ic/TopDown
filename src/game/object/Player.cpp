#include "Player.h"
#include "math/maths.h"
#include <sstream>
#include <cmath>

Player::Player()
        : Player{0, 0} {}

Player::Player(int x, int y)
        : _x(x), _y(y) {
    _hp = Player::get_default_hp();
}

void Player::set_position(float x, float y) {
    _x = x;
    _y = y;
}

float Player::get_x() const { return _x; }

float Player::get_y() const { return _y; }

float Player::get_angle() const { return _angle; }

float Player::get_max_movement_speed() const {
    return _max_movement_speed;
}

void Player::set_x(float x) { _x = x; }

void Player::set_y(float y) { _y = y; }

void Player::set_angle(float a) { _angle = a; }

void Player::set_max_movement_speed(float movementSpeed) {
    if (std::isgreaterequal(movementSpeed, 0.f)) {
        _max_movement_speed = movementSpeed;
    }
}

Circle Player::get_circle() const { return {_x, _y, 30}; }

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
    if (event.get_type() == KeyboardEvent::Type::KeyDown) {
        switch (event.get_key()) {
            case KEY_UP:
            case 'w': {
                _input_state.set(UP_PRESSED);
                break;
            }

            case KEY_DOWN:
            case 's': {
                _input_state.set(DOWN_PRESSED);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                _input_state.set(LEFT_PRESSED);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                _input_state.set(RIGHT_PRESSED);
                break;
            }

            case KEY_SPACE: {
                _input_state.set(TRIGGER_PRESSED);
                break;
            }

            default: {
                break;
            }
        }
    } else if (event.get_type() == KeyboardEvent::Type::KeyUp) {
        switch (event.get_key()) {
            case KEY_UP:
            case 'w': {
                _input_state.reset(UP_PRESSED);
                break;
            }

            case KEY_DOWN:
            case 's': {
                _input_state.reset(DOWN_PRESSED);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                _input_state.reset(LEFT_PRESSED);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                _input_state.reset(RIGHT_PRESSED);
                break;
            }

            case KEY_SPACE: {
                _input_state.reset(TRIGGER_PRESSED);
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


void Player::handle_mouse_event(const MouseEvent& event) {
    switch (event.get_type()) {
        case MouseEvent::Type::ScrollUp: {
            select_previous_weapon();
            break;
        }

        case MouseEvent::Type::ScrollDown: {
            select_next_weapon();
            break;
        }

        case MouseEvent::Type::ButtonDown: {
            _input_state.set(TRIGGER_PRESSED);
            break;
        }

        case MouseEvent::Type::ButtonUp: {
            _input_state.reset(TRIGGER_PRESSED);
            break;
        }

        case MouseEvent::Type::Motion: {
            _angle = math::get_cartesian_angle(get_x(), get_y(), event.get_x(), event.get_y());
            break;
        }
    }
}

void Player::handle_logic(Random& random, Engine& resources, Audio& audio) {
    // TODO Make the timer store a pointer to clock
    // TODO AFTER Move the condition inside the getter
    set_max_movement_speed(_damage_cooldown.ticks_passed_since_start(resources.get_clock(), 500) ? 2.3f : 1.0f);

    update_speeds();

    default_move();

    if (!_weapons.empty()) {
        // TODO don't try to reload on every frame
        _weapons[_selected_weapon_index].try_reload(resources.get_clock());
        if (_input_state.test(TRIGGER_PRESSED)) {
            _weapons[_selected_weapon_index].pull_trigger(random, resources, audio, *this);
        }
    }
}

void Player::update_speeds() {
    // TODO extract speed calculations to share between classes
    int direction_x = _input_state.test(RIGHT_PRESSED) - _input_state.test(LEFT_PRESSED);
    int direction_y = _input_state.test(DOWN_PRESSED) - _input_state.test(UP_PRESSED);

    if (direction_x != 0 || direction_y != 0) {
        auto movement_angle = math::get_radian_angle(0, 0, direction_x, direction_y);

        float speed_x = math::radian_cos(movement_angle) * get_max_movement_speed();
        float speed_y = math::radian_sin(movement_angle) * get_max_movement_speed();

        set_current_speed(speed_x, speed_y);
    } else {
        set_current_speed(0, 0);
    }
}

void Player::handle_render(Engine& resources, GraphicContext& graphicContext, float predictionRatio) {
    default_render(resources, graphicContext, predictionRatio);
    default_render_health(graphicContext, Color{0, 0x77, 0, 0xFF}, 0);
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

float Player::get_current_speed_x() const {
    return _current_speed_x;
}

float Player::get_current_speed_y() const {
    return _current_speed_y;
}

void Player::set_current_speed_x(float speedX) {
    _current_speed_x = speedX;
}

void Player::set_current_speed_y(float speedY) {
    _current_speed_y = speedY;
}

void Player::set_current_speed(float speedX, float speedY) {
    set_current_speed_x(speedX);
    set_current_speed_y(speedY);
}
