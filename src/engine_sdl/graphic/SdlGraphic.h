#pragma once

#include "engine/graphic/Graphic.h"
#include "SdlTexture.h"
#include <unordered_map>

class SdlGraphic : public Graphic {
public:
    SdlGraphic(int screen_width, int screen_height);

    ~SdlGraphic() override;

    void refresh_screen() override;

    void clear_screen() override;

    void render_box(const Box& box, const Color& color) override;

    void render(const std::string& texture_name, int x, int y) override;

    void render(const std::string& texture_name, int x, int y, float angle) override;

    int get_screen_width() override;

    int get_screen_height() override;

    Texture get_texture(const std::string& name) override;

    void load_texture(const std::string& name, const char* path) override;

    struct FailedToLoadTextureException : public std::runtime_error {
        explicit FailedToLoadTextureException(const char* message);
    };

private:
    void render(const SdlTexture& texture, int x, int y);

    void render(const SdlTexture& texture, int x, int y, float angle);

    SdlTexture load_texture(const char* path);

    struct SdlDeleter {
        void operator()(SDL_Window* p);

        void operator()(SDL_Renderer* p);
    };

    std::unordered_map<std::string, SdlTexture> _name_to_texture;
    std::unique_ptr<SDL_Window, SdlDeleter> _window;
    std::unique_ptr<SDL_Renderer, SdlDeleter> _renderer;
};
