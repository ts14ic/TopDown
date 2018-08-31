#pragma once

#include "engine/graphic/GraphicContext.h"
#include "engine/graphic/Texture.h"
#include "SdlTexture.h"

class SdlGraphicContext : public GraphicContext {
public:
    SdlGraphicContext(int screen_width, int screen_height);

    void refresh_screen() override;

    void clear_screen() override;

    void render_box(const Box& box, const Color& color) override;

    void render(const Texture& texture, int x, int y) override;

    void render(const Texture& texture, int x, int y, float angle) override;

    int get_screen_width() override;

    int get_screen_height() override;

    SdlTexture load_texture(const char* path);

    struct FailedSdlInitException : public std::runtime_error {
        explicit FailedSdlInitException(const char* message);
    };

    struct FailedToLoadTextureException : public std::runtime_error {
        explicit FailedToLoadTextureException(const char* message);
    };

private:
    struct SdlDeleter {
        void operator()(SDL_Window* p);

        void operator()(SDL_Renderer* p);
    };

    std::unique_ptr<SDL_Window, SdlDeleter> _window;
    std::unique_ptr<SDL_Renderer, SdlDeleter> _renderer;
};
