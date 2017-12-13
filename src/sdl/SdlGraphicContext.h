//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/GraphicContext.h"
#include <memory>

class Texture;

class SdlTexture;

struct SDL_Renderer;
struct SDL_Window;

class SdlGraphicContext : public GraphicContext {
public:
    SdlGraphicContext(int screenWidth, int screenHeight);

    ~SdlGraphicContext() override;

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

    SDL_Renderer* getRenderer();

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
