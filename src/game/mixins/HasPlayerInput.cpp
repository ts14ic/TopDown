#include "HasPlayerInput.h"
#include <io/files/files.h>
#include <io/json/json.h>
#include <iostream>

HasPlayerInput::HasPlayerInput(cstring control_scheme_file_name) {
    auto file = files::read_file_to_string(control_scheme_file_name);
    auto document = json::parse_json(file);

    auto read_hold_action = [&](cstring key, PlayerInput::HoldAction value) {
        _key_to_hold_action[json::get_int(document, key)] = value;
    };
    read_hold_action("/controls/hold/up", PlayerInput::HOLD_UP);
    read_hold_action("/controls/hold/left", PlayerInput::HOLD_LEFT);
    read_hold_action("/controls/hold/down", PlayerInput::HOLD_DOWN);
    read_hold_action("/controls/hold/right", PlayerInput::HOLD_RIGHT);
    read_hold_action("/controls/hold/trigger", PlayerInput::HOLD_TRIGGER);

    auto read_quick_action = [&](cstring key, PlayerInput::QuickAction value) {
        _key_to_quick_action[json::get_int(document, key)] = value;
    };
    read_quick_action("/controls/quick/0", PlayerInput::QUICK_0);
    read_quick_action("/controls/quick/1", PlayerInput::QUICK_1);
    read_quick_action("/controls/quick/2", PlayerInput::QUICK_2);
    read_quick_action("/controls/quick/3", PlayerInput::QUICK_3);
    read_quick_action("/controls/quick/4", PlayerInput::QUICK_4);
    read_quick_action("/controls/quick/5", PlayerInput::QUICK_5);
    read_quick_action("/controls/quick/6", PlayerInput::QUICK_6);
    read_quick_action("/controls/quick/7", PlayerInput::QUICK_7);
    read_quick_action("/controls/quick/8", PlayerInput::QUICK_8);
    read_quick_action("/controls/quick/9", PlayerInput::QUICK_9);
    read_quick_action("/controls/quick/next_weapon", PlayerInput::QUICK_NEXT_WEAPON);
    read_quick_action("/controls/quick/previous_weapon", PlayerInput::QUICK_PREVIOUS_WEAPON);
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

template<typename Mutator>
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

void HasPlayerInput::move_mouse(Point2d<int> mouse_position) {
    mutate_input(this, [=](PlayerInput& input) {
        input.move_mouse(mouse_position);
    });
}
