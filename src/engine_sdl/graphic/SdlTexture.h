#pragma once

#include <engine/graphic/Texture.h>
#include <SDL_render.h>
#include <memory>

struct TextureDeleter {
    void operator()(SDL_Texture* p) { SDL_DestroyTexture(p); }
};

using TextureHandle = std::unique_ptr<SDL_Texture, TextureDeleter>;

class SdlTexture {
public:
    SdlTexture() = default;

    SdlTexture(TextureHandle texture, Size2<int> size) : _texture{std::move(texture)} {
        _size = size;
    }

    SdlTexture(const SdlTexture&) = delete;

    SdlTexture(SdlTexture&&) noexcept = default;

    bool is_loaded() const { return _texture != nullptr; }

    Size2<int> get_size() const { return _size; }

    SDL_Texture* get_wrapped_texture() const { return _texture.get(); }

private:
    TextureHandle _texture;
    Size2<int> _size;
};
