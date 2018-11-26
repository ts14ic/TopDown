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
    if (_inventory.any_selected()) {
        std::ostringstream stream;
        stream << "player_" << _inventory.get_selected_name();
        return stream.str();
    } else {
        return "player";
    }
}

bool Player::is_dead() const {
    return !has_hp();
}

void Player::take_damage(int damageAmount) {
    if (damageAmount > 0 && _damage_cooldown.ticks_passed_since_start(500)) {
        _hitpoints.current_hp -= damageAmount;
        _damage_cooldown.restart();
    }
}

void Player::handle_logic(Engine& engine, std::vector<Bullet>& bullets) {
    if (_input.mouse_moved()) {
        _transform.angle = math::get_cartesian_angle(_transform.position, _input.pop_mouse_position());
    }

    handle_weapon_selection();

    // TODO Make the timer store a pointer to clock
    // TODO AFTER Move the condition inside the getter
    _speed.max_speed = _damage_cooldown.ticks_passed_since_start(500) ? 2.3f : 1.0f;

    update_speeds();

    default_move();

    // TODO don't try to reload on every frame
    _inventory.try_reload_selected();

    if (_input.is_held(PlayerInput::HOLD_TRIGGER)) {
        _inventory.fire_from_selected(engine, *this, bullets);
    }
}

void Player::handle_weapon_selection() {
    while (_input.has_quick_actions()) {
        auto action = _input.pop_quick_action();
        if (action == PlayerInput::QUICK_NEXT_WEAPON) {
            _inventory.select_next();
        } else if (action == PlayerInput::QUICK_PREVIOUS_WEAPON) {
            _inventory.select_previous();
        } else if (PlayerInput::is_digit(action)) {
            _inventory.select_by_index(PlayerInput::to_digit(action));
        }
    }
}

void Player::update_speeds() {
    // TODO extract speed calculations to share between classes
    int direction_x = _input.is_held(PlayerInput::HOLD_RIGHT) - _input.is_held(PlayerInput::HOLD_LEFT);
    int direction_y = _input.is_held(PlayerInput::HOLD_DOWN) - _input.is_held(PlayerInput::HOLD_UP);

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

void Player::handle_render(Graphic& graphic, float frames_count) {
    default_render(graphic, frames_count);
    default_render_health(graphic, Color{0, 0x77, 0, 0xFF}, 0);
}
