#include "PlayerInput.h"

void PlayerInput::move_mouse(Point2<int> position) {
    _mouse_position = position;
    _mouse_moved = true;
}

Point2<int> PlayerInput::pop_mouse_position() {
    auto position = get_mouse_position();
    _mouse_moved = false;
    return position;
}

void PlayerInput::hold(PlayerInput::HoldAction action) {
    if (action != HOLD_NONE) {
        _hold_actions.set(action);
    }
}

void PlayerInput::release(PlayerInput::HoldAction action) {
    if (action != HOLD_NONE) {
        _hold_actions.reset(action);
    }
}

bool PlayerInput::is_held(PlayerInput::HoldAction action) {
    return action != HOLD_NONE && _hold_actions.test(action);
}

void PlayerInput::activate(PlayerInput::QuickAction action) {
    if (action != QUICK_NONE) {
        _quick_actions.set(action);
    }
}

bool PlayerInput::has_quick_actions() const {
    return _quick_actions.any();
}

PlayerInput::QuickAction PlayerInput::pop_quick_action() {
    for (unsigned action = QUICK_FIRST_ACTION; action <= QUICK_LAST_ACTION; ++action) {
        if (_quick_actions.test(action)) {
            _quick_actions.reset(action);
            return static_cast<QuickAction>(action);
        }
    }
    return QUICK_NONE;
}

bool PlayerInput::is_digit(PlayerInput::QuickAction action) {
    return action >= QUICK_0 && action <= QUICK_9;
}

unsigned PlayerInput::to_digit(PlayerInput::QuickAction action) {
    return static_cast<unsigned>(action);
}
