#include "sdlwrap.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

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

SDL_Window*& window() {
    static SDL_Window* ret = nullptr;
    return ret;
}

bool init_sdl() {
    int SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if(0 != SDL_Init(SDL_flags)) {
        SDL_Log("Failed SDL_Init. %s.\n", SDL_GetError());
        return false;
    }
    window() = SDL_CreateWindow(
        "TopDown - Reborn",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth(), screenHeight(),
        SDL_WINDOW_SHOWN
    );
    if(!window()) {
        SDL_Log("Failed window creation. %s.\n", SDL_GetError());
        return false;
    }
    
    renderer() = SDL_CreateRenderer(
        window(), -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC
    );
    if(!renderer()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Can't create renderer.\n%s\n", SDL_GetError());
        return false;
    }
    
    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        SDL_Log("Failed IMG_Init. %s.\n", IMG_GetError());
        return false;
    }
    
    if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        SDL_Log("Failed Mix_OpenAudio. %s.\n", Mix_GetError());
        return false;
    }
    
    SDL_SetRenderDrawColor(renderer(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(renderer());
    SDL_RenderPresent(renderer());
    
    SDL_Log("init_sdl(): fine");
    return true;
}

void close_sdl() {
    SDL_Quit();
}
