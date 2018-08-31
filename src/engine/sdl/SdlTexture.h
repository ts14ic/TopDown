#pragma once

#include "engine/resources/Texture.h"
#include <memory>
#include <SDL_render.h>

class SdlTexture : public Texture {
public:
    struct TextureDeleter {
        void operator()(SDL_Texture* p);
    };

    SdlTexture();

    SdlTexture(std::unique_ptr<SDL_Texture, TextureDeleter> texture, int width, int height);

    SdlTexture(SdlTexture const&) = delete;

    SdlTexture(SdlTexture&&) noexcept;

    bool is_loaded() const override;

    int get_width() const override;

    int get_height() const override;

    SDL_Texture* get_wrapped_texture() const;

private:
    std::unique_ptr<SDL_Texture, TextureDeleter> _texture;
    int _width = 0;
    int _height = 0;
};
