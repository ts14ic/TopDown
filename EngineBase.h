#pragma once

#include <SDL_video.h>
#include <memory>
#include <SDL_system.h>

class EngineBase {
public:
    EngineBase();

    EngineBase(int screenWidth, int screenHeight);

    ~EngineBase();

    struct SDLDeleter {
        void operator()(SDL_Window *p) {
            SDL_DestroyWindow(p);
        }

        void operator()(SDL_Renderer* p) {
            SDL_DestroyRenderer(p);
        }
    };

private:
    void init();

private:
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    std::unique_ptr<SDL_Window, SDLDeleter> mWindow;
    std::unique_ptr<SDL_Renderer, SDLDeleter> mRenderer;
};

