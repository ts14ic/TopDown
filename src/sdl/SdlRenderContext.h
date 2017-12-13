//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/RenderContext.h"
#include <memory>

class Texture;

class SdlTexture;

struct SDL_Renderer;
struct SDL_Window;

class SdlRenderContext : public RenderContext {
public:
    SdlRenderContext(int screenWidth, int screenHeight);

    ~SdlRenderContext() override;

    // todo move texture loading here, and make this getter private
    SDL_Renderer* getRenderer();

    void refreshScreen() override;

    void clearScreen() override;

    void renderBox(const Box& box, const Color& color) override;

    void render(Texture const& texture, int x, int y) override;

    void render(Texture const& texture, int x, int y, float angle) override;

    int getScreenWidth() override;

    int getScreenHeight() override;

    SdlTexture loadTexture(const char* path);

    class FailedSDLInitException : public std::runtime_error {
    public:
        explicit FailedSDLInitException(const char* message)
                : runtime_error(message) {}
    };


    struct FailedToLoadTextureException : public std::runtime_error {
        explicit FailedToLoadTextureException(const char* message);
    };

private:
    void init();

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
