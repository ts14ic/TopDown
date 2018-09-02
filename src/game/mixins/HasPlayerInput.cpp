#include "HasPlayerInput.h"

void HasPlayerInput::handle_key_event(const KeyboardEvent& event) {
    if (event.get_type() == KeyboardEvent::Type::KEY_DOWN) {
        switch (event.get_key()) {
            case KEY_UP:
            case 'w': {
                hold(PlayerInput::HOLD_UP);
                break;
            }

            case KEY_DOWN:
            case 's': {
                hold(PlayerInput::HOLD_DOWN);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                hold(PlayerInput::HOLD_LEFT);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                hold(PlayerInput::HOLD_RIGHT);
                break;
            }

            case KEY_SPACE: {
                hold(PlayerInput::HOLD_TRIGGER);
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
                release(PlayerInput::HOLD_UP);
                break;
            }

            case KEY_DOWN:
            case 's': {
                release(PlayerInput::HOLD_DOWN);
                break;
            }

            case KEY_LEFT:
            case 'a': {
                release(PlayerInput::HOLD_LEFT);
                break;
            }

            case KEY_RIGHT:
            case 'd': {
                release(PlayerInput::HOLD_RIGHT);
                break;
            }

            case KEY_SPACE: {
                release(PlayerInput::HOLD_TRIGGER);
                break;
            }

            case ',': {
                activate(PlayerInput::QUICK_PREVIOUS_WEAPON);
                break;
            }

            case '.': {
                activate(PlayerInput::PlayerInput::QUICK_NEXT_WEAPON);
                break;
            }

            default: {
                int key = event.get_key();
                if (key >= '0' && key <= '9') {
                    auto action = PlayerInput::QUICK_9 - ('9' - key);
                    activate(static_cast<PlayerInput::QuickAction>(action));
                }
                break;
            }
        }
    }
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
