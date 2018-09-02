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
    void press(PlayerInput::HoldAction action);

    void release(PlayerInput::HoldAction action);

    void tap(PlayerInput::QuickAction action);

    void move_mouse(Point2<int> mouse_position);
};