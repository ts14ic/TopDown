#pragma once

#include "engine/input/Input.h"
#include <SDL_events.h>

class SdlInput : public Input {
public:
    void poll_events() override;

    void set_event_handler(EventHandler& eventHandler) override;

    void remove_event_handler() override;

private:
    void forward_window_event();

    void forward_mouse_event();

    void forward_keyboard_event();

    WindowEvent _window_event;
    MouseEvent _mouse_event;
    KeyboardEvent _key_event;
    EventHandler* _event_handler;
};

int transform_sdl_key_code(SDL_Keycode keyCode);
