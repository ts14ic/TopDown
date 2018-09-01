#pragma once

#include "engine/graphic/Texture.h"
#include <memory>
#include <SDL_render.h>

class SdlTexture {
public:
    struct TextureDeleter {
        void operator()(SDL_Texture* p);
    };

    SdlTexture();

    SdlTexture(std::unique_ptr<SDL_Texture, TextureDeleter> texture, int width, int height);

    SdlTexture(const SdlTexture&) = delete;

    SdlTexture(SdlTexture&&) noexcept;

    bool is_loaded() const;

    int get_width() const;

    int get_height() const;

    SDL_Texture* get_wrapped_texture() const;

private:
    std::unique_ptr<SDL_Texture, TextureDeleter> _texture;
    int _width = 0;
    int _height = 0;
};
