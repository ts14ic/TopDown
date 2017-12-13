//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "RenderContext.h"
#include <memory>

// forward declarations begin
class Assets;

class Texture;

struct SDL_Renderer;
struct SDL_Window;
// forward declarations end

class DefaultRenderContext : public RenderContext {
public:
    DefaultRenderContext(Assets& assets, int screenWidth, int screenHeight);

    ~DefaultRenderContext() override;

    // todo SDL_Renderer is too specific
    SDL_Renderer* getRenderer() override;

    void load_media(Assets& assets) override;

    void render(Texture const& texture, int x, int y) override;

    void render(Texture const& texture, int x, int y, float angle) override;

    int getScreenWidth() override;

    int getScreenHeight() override;

    class FailedSDLInitException : public std::runtime_error {
    public:
        explicit FailedSDLInitException(const char* message)
                : runtime_error(message) {}
    };

private:
    void init();

    void load_texture(Assets& assets, const char* name, const char* filename);

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
