#pragma once

#include <game/components/PlayerInput.h>
#include <engine/input/MouseEventHandler.h>
#include <engine/input/KeyboardEventHandler.h>
#include <unordered_map>

class HasPlayerInput : public KeyboardEventHandler,
                       public MouseEventHandler {
public:
    explicit HasPlayerInput(const char* control_scheme_file_name = "data/config.json");

    virtual PlayerInput get_player_input() const = 0;

    virtual void set_player_input(PlayerInput input) = 0;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

private:
    PlayerInput::HoldAction event_to_hold_action(const KeyboardEvent& event) const;

    PlayerInput::QuickAction event_to_quick_action(const KeyboardEvent& event) const;

    void press(PlayerInput::HoldAction action);

    void release(PlayerInput::HoldAction action);

    void tap(PlayerInput::QuickAction action);

    void move_mouse(Point2<int> mouse_position);

    std::unordered_map<int, PlayerInput::HoldAction> _key_to_hold_action;
    std::unordered_map<int, PlayerInput::QuickAction> _key_to_quick_action;
};