#include "HasPlayerInput.h"
#include <unordered_map>

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
    static std::unordered_map<int, PlayerInput::HoldAction> ACTIONS_MAP{
            {KEY_UP, PlayerInput::HOLD_UP},
            {'w', PlayerInput::HOLD_UP},
            {KEY_DOWN, PlayerInput::HOLD_DOWN},
            {'s', PlayerInput::HOLD_DOWN},
            {KEY_LEFT, PlayerInput::HOLD_LEFT},
            {'a', PlayerInput::HOLD_LEFT},
            {KEY_RIGHT, PlayerInput::HOLD_RIGHT},
            {'d', PlayerInput::HOLD_RIGHT},
            {KEY_SPACE, PlayerInput::HOLD_TRIGGER}
    };
    auto action = ACTIONS_MAP.find(event.get_key());
    return action != ACTIONS_MAP.end()
           ? action->second
           : PlayerInput::HOLD_NONE;
}

PlayerInput::QuickAction event_to_quick_action(const KeyboardEvent& event) {
    static std::unordered_map<int, PlayerInput::QuickAction> ACTIONS_MAP{
            {'0', PlayerInput::QUICK_0},
            {'1', PlayerInput::QUICK_1},
            {'2', PlayerInput::QUICK_2},
            {'3', PlayerInput::QUICK_3},
            {'4', PlayerInput::QUICK_4},
            {'5', PlayerInput::QUICK_5},
            {'6', PlayerInput::QUICK_6},
            {'7', PlayerInput::QUICK_7},
            {'8', PlayerInput::QUICK_8},
            {'9', PlayerInput::QUICK_9},
            {',', PlayerInput::QUICK_PREVIOUS_WEAPON},
            {'.', PlayerInput::QUICK_NEXT_WEAPON},
    };
    auto action = ACTIONS_MAP.find(event.get_key());
    return action != ACTIONS_MAP.end()
           ? action->second
           : PlayerInput::QUICK_NONE;
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
