#pragma once

#include <SDL_video.h>
#include <memory>
#include <SDL_system.h>

class RenderBase {
public:
    RenderBase();

    RenderBase(int screenWidth, int screenHeight);

    ~RenderBase();

    struct SDLDeleter {
        void operator()(SDL_Window* p) {
            SDL_DestroyWindow(p);
        }

        void operator()(SDL_Renderer* p) {
            SDL_DestroyRenderer(p);
        }
    };

    SDL_Renderer* getRenderer();

    void load_media();

    class FailedSDLInitException : std::runtime_error {
    public:
        explicit FailedSDLInitException(const char* message) : runtime_error(message) {}
    };

private:
    void init();

    void load_texture(const char* name, const char* filename);

private:
    int mScreenWidth = 0;
    int mScreenHeight = 0;
    std::unique_ptr<SDL_Window, SDLDeleter> mWindow;
    std::unique_ptr<SDL_Renderer, SDLDeleter> mRenderer;
};

