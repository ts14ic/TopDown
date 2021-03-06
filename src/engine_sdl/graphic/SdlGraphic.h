#pragma once

#include "SdlTexture.h"
#include <engine/graphic/Graphic.h>
#include <unordered_map>

struct SdlDeleter {
    void operator()(SDL_Window* p);

    void operator()(SDL_Renderer* p);
};

using WindowHandle = std::unique_ptr<SDL_Window, SdlDeleter>;
using RendererHandle = std::unique_ptr<SDL_Renderer, SdlDeleter>;

class SdlGraphic : public Graphic {
public:
    SdlGraphic();

    ~SdlGraphic() override;

    void init(int screen_width, int screen_height);

    void deinit();

    void refresh_screen() override;

    void clear_screen() override;

    void render_box(const Box& box, const Color& color) override;

    void render_texture(const std::string& texture_name, Point2d<int> position) override;

    void render_texture(const std::string& texture_name, Point2d<int> position, float angle) override;

    int get_screen_width() override;

    int get_screen_height() override;

    Texture get_texture(const std::string& name) override;

    void load_texture(const std::string& name, cstring path) override;

private:
    void render(const SdlTexture& texture, Point2d<int> position);

    void render(const SdlTexture& texture, Point2d<int> position, float angle);

    SdlTexture load_texture(cstring path);

    std::unordered_map<std::string, SdlTexture> _name_to_texture;
    WindowHandle _window;
    RendererHandle _renderer;
};
