#include "sdlwrap.h"
#include <SDL.h>

int& screenWidth() {
    static int ret = 800;
    return ret;
}

int& screenHeight() {
    static int ret = 600;
    return ret;
}

SDL_Renderer*& renderer() {
    static SDL_Renderer* ret = nullptr;
    return ret;
}
