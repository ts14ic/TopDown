#include "HasPlayerInput.h"

void HasPlayerInput::handle_key_event(const KeyboardEvent& event) {
    PlayerInput::HoldAction action = key_to_hold_action(event);
    if (KeyboardEvent::is_key_down(event)) {
        hold(action);
    } else if (KeyboardEvent::is_key_up(event)) {
        release(action);
    }

    activate(key_to_quick_action(event));
}

PlayerInput::HoldAction HasPlayerInput::key_to_hold_action(const KeyboardEvent& event) const {
    switch (event.get_key()) {
        case KEY_UP:
        case 'w': {
            return PlayerInput::HOLD_UP;
        }

        case KEY_DOWN:
        case 's': {
            return PlayerInput::HOLD_DOWN;
        }

        case KEY_LEFT:
        case 'a': {
            return PlayerInput::HOLD_LEFT;
        }

        case KEY_RIGHT:
        case 'd': {
            return PlayerInput::HOLD_RIGHT;
        }

        case KEY_SPACE: {
            return PlayerInput::HOLD_TRIGGER;
        }

        default: {
            return PlayerInput::HOLD_NONE;
        }
    }
}

PlayerInput::QuickAction HasPlayerInput::key_to_quick_action(const KeyboardEvent& event) const {
    switch (event.get_key()) {
        case ',': {
            if (event.get_type() == KeyboardEvent::Type::KEY_UP) {
                return PlayerInput::QUICK_PREVIOUS_WEAPON;
            }
            break;
        }

        case '.': {
            if (event.get_type() == KeyboardEvent::Type::KEY_UP) {
                return PlayerInput::PlayerInput::QUICK_NEXT_WEAPON;
            }
            break;
        }

        default: {
            if (event.get_type() == KeyboardEvent::Type::KEY_UP) {
                int key = event.get_key();
                if (key >= '0' && key <= '9') {
                    auto action = PlayerInput::QUICK_9 - ('9' - key);
                    return static_cast<PlayerInput::QuickAction>(action);
                }
            }
            break;
        }
    }
    return PlayerInput::QUICK_NONE;
}

void HasPlayerInput::handle_mouse_event(const MouseScrollEvent& event) {
    switch (event.get_type()) {
        case MouseScrollEvent::Type::SCROLL_UP: {
            activate(PlayerInput::QUICK_PREVIOUS_WEAPON);
            break;
        }

        case MouseScrollEvent::Type::SCROLL_DOWN: {
            activate(PlayerInput::QUICK_NEXT_WEAPON);
            break;
        }
    }
}

void HasPlayerInput::handle_mouse_event(const MousePointEvent& event) {
    switch (event.get_type()) {
        case MousePointEvent::Type::BUTTON_DOWN: {
            hold(PlayerInput::HOLD_TRIGGER);
            break;
        }

        case MousePointEvent::Type::BUTTON_UP: {
            release(PlayerInput::HOLD_TRIGGER);
            break;
        }

        case MousePointEvent::Type::MOTION: {
            set_mouse_position(event.get_position());
            break;
        }
    }
}

void HasPlayerInput::hold(PlayerInput::HoldAction action) {
    PlayerInput input = get_player_input();
    input.hold(action);
    set_player_input(input);
}

void HasPlayerInput::release(PlayerInput::HoldAction action) {
    PlayerInput input = get_player_input();
    input.release(action);
    set_player_input(input);
}

void HasPlayerInput::activate(PlayerInput::QuickAction action) {
    PlayerInput input = get_player_input();
    input.activate(action);
    set_player_input(input);
}

void HasPlayerInput::set_mouse_position(Point2<int> mouse_position) {
    PlayerInput input = get_player_input();
    input.move_mouse(mouse_position);
    set_player_input(input);
}
