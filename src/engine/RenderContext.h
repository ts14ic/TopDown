#pragma once

#include <SDL_video.h>
#include <SDL_system.h>
#include <memory>

class RenderContext {
public:
    RenderContext();

    RenderContext(int screenWidth, int screenHeight);

    ~RenderContext();

    SDL_Renderer* getRenderer();

    void load_media();

    int getScreenWidth();

    int getScreenHeight();

    class FailedSDLInitException : std::runtime_error {
    public:
        explicit FailedSDLInitException(const char* message) : runtime_error(message) {}
    };

private:
    void init();

    void load_texture(const char* name, const char* filename);

private:
    struct SDLDeleter {
        void operator()(SDL_Window* p);

        void operator()(SDL_Renderer* p);
    };

    int mScreenWidth;
    int mScreenHeight;
    std::unique_ptr<SDL_Window, SDLDeleter> mWindow;
    std::unique_ptr<SDL_Renderer, SDLDeleter> mRenderer;
};

