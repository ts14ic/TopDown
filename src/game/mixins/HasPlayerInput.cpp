#include "HasPlayerInput.h"
#include <io/files/files.h>
#include <io/json/json.h>
#include <iostream>

HasPlayerInput::HasPlayerInput(const char* control_scheme_file_name) {
    auto file = files::read_file_to_string(control_scheme_file_name);
    auto document = json::parse_json(file);

    _key_to_hold_action[json::get_int(document, "/controls/hold/up")] = PlayerInput::HOLD_UP;
    _key_to_hold_action[json::get_int(document, "/controls/hold/left")] = PlayerInput::HOLD_LEFT;
    _key_to_hold_action[json::get_int(document, "/controls/hold/down")] = PlayerInput::HOLD_DOWN;
    _key_to_hold_action[json::get_int(document, "/controls/hold/right")] = PlayerInput::HOLD_RIGHT;
    _key_to_hold_action[json::get_int(document, "/controls/hold/trigger")] = PlayerInput::HOLD_TRIGGER;

    _key_to_quick_action[json::get_int(document, "/controls/quick/0")] = PlayerInput::QUICK_0;
    _key_to_quick_action[json::get_int(document, "/controls/quick/1")] = PlayerInput::QUICK_1;
    _key_to_quick_action[json::get_int(document, "/controls/quick/2")] = PlayerInput::QUICK_2;
    _key_to_quick_action[json::get_int(document, "/controls/quick/3")] = PlayerInput::QUICK_3;
    _key_to_quick_action[json::get_int(document, "/controls/quick/4")] = PlayerInput::QUICK_4;
    _key_to_quick_action[json::get_int(document, "/controls/quick/5")] = PlayerInput::QUICK_5;
    _key_to_quick_action[json::get_int(document, "/controls/quick/6")] = PlayerInput::QUICK_6;
    _key_to_quick_action[json::get_int(document, "/controls/quick/7")] = PlayerInput::QUICK_7;
    _key_to_quick_action[json::get_int(document, "/controls/quick/8")] = PlayerInput::QUICK_8;
    _key_to_quick_action[json::get_int(document, "/controls/quick/9")] = PlayerInput::QUICK_9;
    _key_to_quick_action[json::get_int(document, "/controls/quick/next_weapon")] = PlayerInput::QUICK_NEXT_WEAPON;
    _key_to_quick_action[json::get_int(document, "/controls/quick/previous_weapon")] = PlayerInput::QUICK_PREVIOUS_WEAPON;
}

PlayerInput::HoldAction HasPlayerInput::event_to_hold_action(const KeyboardEvent& event) const {
    auto action = _key_to_hold_action.find(event.get_key());
    return action != _key_to_hold_action.end()
           ? action->second
           : PlayerInput::HOLD_NONE;
}

PlayerInput::QuickAction HasPlayerInput::event_to_quick_action(const KeyboardEvent& event) const {
    auto action = _key_to_quick_action.find(event.get_key());
    return action != _key_to_quick_action.end()
           ? action->second
           : PlayerInput::QUICK_NONE;
}

void HasPlayerInput::handle_key_event(const KeyboardEvent& event) {
    if (KeyboardEvent::is_key_down(event)) {
        press(event_to_hold_action(event));
    } else if (KeyboardEvent::is_key_up(event)) {
        release(event_to_hold_action(event));
        tap(event_to_quick_action(event));
    }
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
