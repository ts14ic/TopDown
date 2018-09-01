#include "SdlInput.h"

void SdlInput::poll_events(EventHandler& eventHandler) {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                mWindowEvent.set_type(WindowEvent::Type::Close);
                forward_window_event(eventHandler);
                break;
            }

            case SDL_KEYDOWN: {
                mKeyEvent.set_type(KeyboardEvent::Type::KeyDown);
                mKeyEvent.set_key(transform_sdl_key_code(event.key.keysym.sym));
                forward_keyboard_event(eventHandler);
                break;
            }

            case SDL_KEYUP: {
                mKeyEvent.set_type(KeyboardEvent::Type::KeyUp);
                mKeyEvent.set_key(transform_sdl_key_code(event.key.keysym.sym));
                forward_keyboard_event(eventHandler);
                break;
            }

            case SDL_MOUSEMOTION: {
                mMouseEvent.set_type(MouseEvent::Type::Motion);
                mMouseEvent.set_x(event.motion.x);
                mMouseEvent.set_y(event.motion.y);
                forward_mouse_event(eventHandler);
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                mMouseEvent.set_type(MouseEvent::Type::ButtonUp);
                mMouseEvent.set_x(event.button.x);
                mMouseEvent.set_y(event.button.y);
                forward_mouse_event(eventHandler);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: {
                mMouseEvent.set_type(MouseEvent::Type::ButtonDown);
                mMouseEvent.set_x(event.button.x);
                mMouseEvent.set_y(event.button.y);
                forward_mouse_event(eventHandler);
                break;
            }

            case SDL_MOUSEWHEEL: {
                if (event.wheel.y > 0) {
                    mMouseEvent.set_type(MouseEvent::Type::ScrollUp);
                    mMouseEvent.set_scroll_amount(event.wheel.y);
                } else {
                    mMouseEvent.set_type(MouseEvent::Type::ScrollDown);
                    mMouseEvent.set_scroll_amount(-event.wheel.y);
                }
                forward_mouse_event(eventHandler);
                break;
            }

            default: {
                break;
            }
        }
    }
}

void SdlInput::forward_window_event(WindowEventHandler& eventHandler) {
    eventHandler.handle_window_event(mWindowEvent);
}

void SdlInput::forward_mouse_event(MouseEventHandler& eventHandler) {
    eventHandler.handle_mouse_event(mMouseEvent);
}

void SdlInput::forward_keyboard_event(KeyboardEventHandler& eventHandler) {
    eventHandler.handle_key_event(mKeyEvent);
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