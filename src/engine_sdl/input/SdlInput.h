#pragma once

#include "engine/input/Input.h"
#include <SDL_events.h>

class SdlInput : public Input {
public:
    void poll_events() override;

    void set_event_handler(EventHandler& eventHandler) override;

    void remove_event_handler() override;

private:
    void forward_window_event(WindowEvent::Type type);

    void forward_mouse_event(MouseScrollEvent mouse_scroll_event);

    void forward_mouse_event(MousePointEvent mouse_point_event);

    void forward_keyboard_event(KeyboardEvent::Type type, KeyboardKey_t key);

    EventHandler* _event_handler;
};

int transform_sdl_key_code(SDL_Keycode keyCode);
