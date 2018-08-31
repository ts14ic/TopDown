#pragma once

#include "engine/graphic/GraphicContext.h"
#include "engine/graphic/Texture.h"
#include "SdlTexture.h"

class SdlGraphicContext : public GraphicContext {
public:
    SdlGraphicContext(SDL_Window* window, SDL_Renderer* renderer);

    void refresh_screen() override;

    void clear_screen() override;

    void render_box(const Box &box, const Color &color) override;

    void render(Texture const& texture, int x, int y) override;

    void render(Texture const& texture, int x, int y, float angle) override;

    int get_screen_width() override;

    int get_screen_height() override;

private:
    int _screen_width;
    int _screen_height;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
};
