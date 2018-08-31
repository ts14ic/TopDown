#include "SdlInputContext.h"
#include "SdlInputContext_transformSdlKeyCode.h"

void SdlInputContext::pollEvents(EventHandler& eventHandler) {
    SDL_Event event{};
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: {
                mWindowEvent.setType(WindowEvent::Type::Close);
                forwardWindowEvent(eventHandler);
                break;
            }

            case SDL_KEYDOWN: {
                mKeyEvent.setType(KeyboardEvent::Type::KeyDown);
                mKeyEvent.setKey(transformSdlKeyCode(event.key.keysym.sym));
                forwardKeyboardEvent(eventHandler);
                break;
            }

            case SDL_KEYUP: {
                mKeyEvent.setType(KeyboardEvent::Type::KeyUp);
                mKeyEvent.setKey(transformSdlKeyCode(event.key.keysym.sym));
                forwardKeyboardEvent(eventHandler);
                break;
            }

            case SDL_MOUSEMOTION: {
                mMouseEvent.setType(MouseEvent::Type::Motion);
                mMouseEvent.setX(event.motion.x);
                mMouseEvent.setY(event.motion.y);
                forwardMouseEvent(eventHandler);
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                mMouseEvent.setType(MouseEvent::Type::ButtonUp);
                mMouseEvent.setX(event.button.x);
                mMouseEvent.setY(event.button.y);
                forwardMouseEvent(eventHandler);
                break;
            }

            case SDL_MOUSEBUTTONDOWN: {
                mMouseEvent.setType(MouseEvent::Type::ButtonDown);
                mMouseEvent.setX(event.button.x);
                mMouseEvent.setY(event.button.y);
                forwardMouseEvent(eventHandler);
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
                forwardMouseEvent(eventHandler);
                break;
            }

            default: {
                break;
            }
        }
    }
}

void SdlInputContext::forwardWindowEvent(WindowEventHandler& eventHandler) {
    eventHandler.handleWindowEvent(mWindowEvent);
}

void SdlInputContext::forwardMouseEvent(MouseEventHandler& eventHandler) {
    eventHandler.handleMouseEvent(mMouseEvent);
}

void SdlInputContext::forwardKeyboardEvent(KeyboardEventHandler& eventHandler) {
    eventHandler.handleKeyEvent(mKeyEvent);
}
