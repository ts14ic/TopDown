#pragma once

#include "engine/graphic/Texture.h"
#include <SDL_render.h>
#include <memory>

struct TextureDeleter {
    void operator()(SDL_Texture* p);
};

using TextureHandle = std::unique_ptr<SDL_Texture, TextureDeleter>;

class SdlTexture {
public:
    SdlTexture();

    SdlTexture(TextureHandle texture, int width, int height);

    SdlTexture(const SdlTexture&) = delete;

    SdlTexture(SdlTexture&&) noexcept;

    bool is_loaded() const;

    int get_width() const;

    int get_height() const;

    SDL_Texture* get_wrapped_texture() const;

private:
    TextureHandle _texture;
    int _width = 0;
    int _height = 0;
};
