#pragma once

#include <SDL_video.h>
#include <memory>
#include <SDL_system.h>

struct SdlDeleter {
    void operator()(SDL_Window *p) {
        SDL_DestroyWindow(p);
    }

    void operator()(SDL_Renderer* p) {
        SDL_DestroyRenderer(p);
    }
};

class EngineBase {
public:
    explicit EngineBase();

    EngineBase(int screenWidth, int screenHeight);

    ~EngineBase();

private:
    void init();

private:
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    std::unique_ptr<SDL_Window, SdlDeleter> mWindow;
    std::unique_ptr<SDL_Renderer, SdlDeleter> mRenderer;
};

