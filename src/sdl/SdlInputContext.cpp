#include "SdlInputContext.h"
#include "SdlInputContext_transform_sdl_key_code.h"

void SdlInputContext::poll_events(EventHandler &eventHandler) {
    SDL_Event event{};
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
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
                if(event.wheel.y > 0) {
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

void SdlInputContext::forward_window_event(WindowEventHandler &eventHandler) {
    eventHandler.handle_window_event(mWindowEvent);
}

void SdlInputContext::forward_mouse_event(MouseEventHandler &eventHandler) {
    eventHandler.handle_mouse_event(mMouseEvent);
}

void SdlInputContext::forward_keyboard_event(KeyboardEventHandler &eventHandler) {
    eventHandler.handle_key_event(mKeyEvent);
}