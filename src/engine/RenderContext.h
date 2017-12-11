#pragma once

#include <memory>

// forward declarations begin
class Assets;

class Texture;
struct SDL_Renderer;
struct SDL_Window;
// forward declarations end

class RenderContext {
public:
    RenderContext(Assets& assets, int screenWidth, int screenHeight);

    ~RenderContext();

    SDL_Renderer* getRenderer();

    void load_media(Assets& assets);

    void render(Texture const& texture, int x, int y);

    void render(Texture const& texture, int x, int y, float angle);

    int getScreenWidth();

    int getScreenHeight();

    class FailedSDLInitException : std::runtime_error {
    public:
        explicit FailedSDLInitException(const char* message) : runtime_error(message) {}
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

