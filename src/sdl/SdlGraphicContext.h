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

    void refreshScreen() override;

    void clearScreen() override;

    void renderBox(const Box& box, const Color& color) override;

    void render(Texture const& texture, int x, int y) override;

    void render(Texture const& texture, int x, int y, float angle) override;

    int getScreenWidth() override;

    int getScreenHeight() override;

    SdlTexture loadTexture(const char* path);

    struct SdlDeleter {
        void operator()(SDL_Window* p);

        void operator()(SDL_Renderer* p);
    };

    void setSdlRenderer(
            std::unique_ptr<SDL_Window, SdlDeleter> sdlWindow,
            std::unique_ptr<SDL_Renderer, SdlDeleter> sdlRenderer
    );

    struct FailedToLoadTextureException : public std::runtime_error {
        explicit FailedToLoadTextureException(const char* message);
    };

private:
    SDL_Renderer* getRenderer();

private:
    int mScreenWidth;
    int mScreenHeight;
    std::unique_ptr<SDL_Window, SdlDeleter> mWindow;
    std::unique_ptr<SDL_Renderer, SdlDeleter> mRenderer;
};
