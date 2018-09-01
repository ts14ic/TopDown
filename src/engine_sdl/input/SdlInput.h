#pragma once

#include "engine/input/Input.h"
#include <SDL_events.h>

class SdlInput : public Input {
public:
    void poll_events(EventHandler &eventHandler) override;

protected:
    void forward_window_event(WindowEventHandler &eventHandler) override;

    void forward_mouse_event(MouseEventHandler &eventHandler) override;

    void forward_keyboard_event(KeyboardEventHandler &eventHandler) override;

private:
    WindowEvent _window_event;
    MouseEvent _mouse_event;
    KeyboardEvent _key_event;
};

int transform_sdl_key_code(SDL_Keycode keyCode);
