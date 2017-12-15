//
// Created by ts14ic on 12/13/17.
//

#include "SdlInputContext.h"
#include "../event/EventHandler.h"

void SdlInputContext::pollEvents(EventHandler &eventHandler) {
    SDL_Event event{};
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: {
                mWindowEvent.setType(WindowEvent::Type::Close);
                eventHandler.handleWindowEvent(mWindowEvent);
                break;
            }

            case SDL_KEYDOWN: {
                // TODO transform to own codes (see SDL_keycode.h for available commands)
                mKeyEvent.setType(KeyboardEvent::Type::KeyDown);
                mKeyEvent.setKey(event.key.keysym.sym);
                eventHandler.handleKeyEvent(mKeyEvent);
                break;
            }

            case SDL_KEYUP: {
                mKeyEvent.setType(KeyboardEvent::Type::KeyUp);
                mKeyEvent.setKey(event.key.keysym.sym);
                eventHandler.handleKeyEvent(mKeyEvent);
                break;
            }

            case SDL_MOUSEMOTION: {
                mMouseEvent.setType(MouseEvent::Type::Motion);
                mMouseEvent.setX(event.motion.x);
                mMouseEvent.setY(event.motion.y);
                eventHandler.handleMouseEvent(mMouseEvent);
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                mMouseEvent.setType(MouseEvent::Type::ButtonUp);
                mMouseEvent.setX(event.button.x);
                mMouseEvent.setY(event.button.y);
                eventHandler.handleMouseEvent(mMouseEvent);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: {
                mMouseEvent.setType(MouseEvent::Type::ButtonDown);
                mMouseEvent.setX(event.button.x);
                mMouseEvent.setY(event.button.y);
                eventHandler.handleMouseEvent(mMouseEvent);
                break;
            }

            case SDL_MOUSEWHEEL: {
                if(event.wheel.y > 0) {
                    mMouseEvent.setType(MouseEvent::Type::ScrollUp);
                    mMouseEvent.setScrollAmount(event.wheel.y);
                } else {
                    mMouseEvent.setType(MouseEvent::Type::ScrollDown);
                    mMouseEvent.setScrollAmount(-event.wheel.y);
                }
                eventHandler.handleMouseEvent(mMouseEvent);
                break;
            }

            default: {
                break;
            }
        }
    }
}

void SdlInputContext::forwardWindowEvent(WindowEventHandler &eventHandler) {
    // TODO stub
}

void SdlInputContext::forwardMouseEvent(MouseEventHandler &eventHandler) {
    // TODO stub
}

void SdlInputContext::forwardKeyboardEvent(KeyboardEventHandler &eventHandler) {
    // TODO stub
}
