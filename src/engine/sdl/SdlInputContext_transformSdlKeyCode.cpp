//
// Created by ts14ic on 12/15/17.
//
#include "SdlInputContext_transformSdlKeyCode.h"
#include "../input/KeyboardKey.h"

KeyboardKey_t transformSdlKeyCode(SDL_Keycode keyCode) {
    switch(keyCode) {
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