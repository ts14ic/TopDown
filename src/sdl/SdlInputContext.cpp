//
// Created by ts14ic on 12/13/17.
//

#include "SdlInputContext.h"
#include "../event/EventHandler.h"

void SdlInputContext::pollEvents(EventHandler &eventHandler) {
    while(SDL_PollEvent(&mInputEvent)) {
        switch(mInputEvent.type) {
            case SDL_QUIT: {
                eventHandler.handleWindowEvent();
                break;
            }

            default: {
                break;
            }
        }
    }
    // TODO stub
//    auto& event = engine.getInputContext();
//
//    while(SDL_PollEvent(&event.getInputEvent())) {
//        switch(event.getInputEvent().type) {
//            case SDL_QUIT: {
//                engine.requestStateChange(GState::exit);
//                break;
//            }
//
//            case SDL_KEYDOWN: {
//                switch(event.getInputEvent().key.keysym.sym) {
//                    case SDLK_q:
//                        engine.requestStateChange(GState::exit);
//                        break;
//
//                    case SDLK_RETURN:
//                    case SDLK_ESCAPE:
//                        engine.requestStateChange(GState::moon);
//                        break;
//
//                    default:
//                        break;
//                }
//                break;
//            }
//
//            default:;
//        }
//    }
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
