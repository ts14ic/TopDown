#include "SdlTexture.h"

void TextureDeleter::operator()(SDL_Texture* p) {
    SDL_DestroyTexture(p);
}

SdlTexture::SdlTexture() = default;

SdlTexture::SdlTexture(SdlTexture&& other) noexcept = default;

SdlTexture::SdlTexture(TextureHandle texture, int width, int height)
        : _texture{std::move(texture)}, _width{width}, _height{height} {
}

bool SdlTexture::is_loaded() const {
    return _texture != nullptr;
}

SDL_Texture* SdlTexture::get_wrapped_texture() const {
    return _texture.get();
}

int SdlTexture::get_width() const { return _width; }

int SdlTexture::get_height() const { return _height; }

