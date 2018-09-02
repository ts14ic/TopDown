#pragma once

#include <game/components/PlayerInput.h>
#include <engine/input/MouseEventHandler.h>
#include <engine/input/KeyboardEventHandler.h>

class HasPlayerInput : public KeyboardEventHandler,
                       public MouseEventHandler {
public:
    virtual PlayerInput get_player_input() const = 0;

    virtual void set_player_input(PlayerInput input) = 0;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

private:
    PlayerInput::HoldAction key_to_hold_action(const KeyboardEvent& event) const;

    PlayerInput::QuickAction key_to_quick_action(const KeyboardEvent& event) const;

    void hold(PlayerInput::HoldAction action);

    void release(PlayerInput::HoldAction action);

    void activate(PlayerInput::QuickAction action);

    void set_mouse_position(Point2<int> mouse_position);
};