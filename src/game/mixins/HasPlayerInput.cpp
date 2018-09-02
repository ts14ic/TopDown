#include "HasPlayerInput.h"

PlayerInput::HoldAction event_to_hold_action(const KeyboardEvent& event);

PlayerInput::QuickAction event_to_quick_action(const KeyboardEvent& event);

void HasPlayerInput::handle_key_event(const KeyboardEvent& event) {
    if (KeyboardEvent::is_key_down(event)) {
        press(event_to_hold_action(event));
    } else if (KeyboardEvent::is_key_up(event)) {
        release(event_to_hold_action(event));
        tap(event_to_quick_action(event));
    }
}

PlayerInput::HoldAction event_to_hold_action(const KeyboardEvent& event) {
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

PlayerInput::QuickAction event_to_quick_action(const KeyboardEvent& event) {
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
            tap(PlayerInput::QUICK_PREVIOUS_WEAPON);
            break;
        }

        case MouseScrollEvent::Type::SCROLL_DOWN: {
            tap(PlayerInput::QUICK_NEXT_WEAPON);
            break;
        }
    }
}

void HasPlayerInput::handle_mouse_event(const MousePointEvent& event) {
    switch (event.get_type()) {
        case MousePointEvent::Type::BUTTON_DOWN: {
            press(PlayerInput::HOLD_TRIGGER);
            break;
        }

        case MousePointEvent::Type::BUTTON_UP: {
            release(PlayerInput::HOLD_TRIGGER);
            break;
        }

        case MousePointEvent::Type::MOTION: {
            move_mouse(event.get_position());
            break;
        }
    }
}

template <typename Mutator>
void mutate_input(HasPlayerInput* self, Mutator&& mutator) {
    auto input = self->get_player_input();
    mutator(input);
    self->set_player_input(input);
}

void HasPlayerInput::press(PlayerInput::HoldAction action) {
    mutate_input(this, [=](PlayerInput& input) {
        input.press(action);
    });
}

void HasPlayerInput::release(PlayerInput::HoldAction action) {
    mutate_input(this, [=](PlayerInput& input) {
        input.release(action);
    });
}

void HasPlayerInput::tap(PlayerInput::QuickAction action) {
    mutate_input(this, [=](PlayerInput& input) {
        input.tap(action);
    });
}

void HasPlayerInput::move_mouse(Point2<int> mouse_position) {
    mutate_input(this, [=](PlayerInput& input) {
        input.move_mouse(mouse_position);
    });
}
