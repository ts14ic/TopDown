#include "SdlInput.h"

void SdlInput::set_event_handler(EventHandler& eventHandler) {
    _event_handler = &eventHandler;
}

void SdlInput::remove_event_handler() {
    _event_handler = nullptr;
}

void SdlInput::poll_events() {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                forward_window_event(WindowEvent::Type::Close);
                break;
            }

            case SDL_KEYDOWN: {
                forward_keyboard_event(KeyboardEvent::Type::KeyDown, transform_sdl_key_code(event.key.keysym.sym));
                break;
            }

            case SDL_KEYUP: {
                forward_keyboard_event(KeyboardEvent::Type::KeyUp, transform_sdl_key_code(event.key.keysym.sym));
                break;
            }

            case SDL_MOUSEMOTION: {
                forward_mouse_event(MousePointEvent{
                        MousePointEvent::Type::Motion,
                        event.motion.x,
                        event.motion.y
                });
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                forward_mouse_event(MousePointEvent{
                        MousePointEvent::Type::ButtonUp,
                        event.button.x,
                        event.button.y
                });
                break;
            }

            case SDL_MOUSEBUTTONDOWN: {
                forward_mouse_event(MousePointEvent{
                        MousePointEvent::Type::ButtonDown,
                        event.button.x,
                        event.button.y
                });
                break;
            }

            case SDL_MOUSEWHEEL: {
                if (event.wheel.y > 0) {
                    forward_mouse_event(MouseScrollEvent{
                            MouseScrollEvent::Type::ScrollUp,
                            event.wheel.y
                    });
                } else {
                    forward_mouse_event(MouseScrollEvent{
                            MouseScrollEvent::Type::ScrollDown,
                            -event.wheel.y
                    });
                }
                break;
            }

            default: {
                break;
            }
        }
    }
}

void SdlInput::forward_window_event(WindowEvent::Type type) {
    if (_event_handler != nullptr) {
        _event_handler->handle_window_event(WindowEvent{type});
    }
}

void SdlInput::forward_mouse_event(MouseScrollEvent mouse_scroll_event) {
    if (_event_handler != nullptr) {
        _event_handler->handle_mouse_event(mouse_scroll_event);
    }
}

void SdlInput::forward_mouse_event(MousePointEvent mouse_point_event) {
    if (_event_handler != nullptr) {
        _event_handler->handle_mouse_event(mouse_point_event);
    }
}

void SdlInput::forward_keyboard_event(KeyboardEvent::Type type, KeyboardKey_t key) {
    if (_event_handler != nullptr) {
        _event_handler->handle_key_event(KeyboardEvent{type, key});
    }
}

KeyboardKey_t transform_sdl_key_code(SDL_Keycode keyCode) {
    switch (keyCode) {
        case SDLK_RETURN:
            return KEY_RETURN;

        case SDLK_ESCAPE:
            return KEY_ESCAPE;

        case SDLK_BACKSPACE:
            return KEY_BACKSPACE;

        case SDLK_TAB:
            return KEY_TAB;

        case SDLK_SPACE:
            return KEY_SPACE;

        case SDLK_CAPSLOCK:
            return KEY_CAPSLOCK;

        case SDLK_F1:
            return KEY_F1;

        case SDLK_F2:
            return KEY_F2;

        case SDLK_F3:
            return KEY_F3;

        case SDLK_F4:
            return KEY_F4;

        case SDLK_F5:
            return KEY_F5;

        case SDLK_F6:
            return KEY_F6;

        case SDLK_F7:
            return KEY_F7;

        case SDLK_F8:
            return KEY_F8;

        case SDLK_F9:
            return KEY_F9;

        case SDLK_F10:
            return KEY_F10;

        case SDLK_F11:
            return KEY_F11;

        case SDLK_F12:
            return KEY_F12;

        case SDLK_LEFT:
            return KEY_LEFT;

        case SDLK_RIGHT:
            return KEY_RIGHT;

        case SDLK_UP:
            return KEY_UP;

        case SDLK_DOWN:
            return KEY_DOWN;

        default:
            return keyCode;
    }
}