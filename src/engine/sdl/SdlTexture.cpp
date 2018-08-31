#include "SdlTexture.h"

SdlTexture::SdlTexture() = default;

SdlTexture::SdlTexture(SdlTexture&& other) noexcept = default;

SdlTexture::SdlTexture(std::unique_ptr<SDL_Texture, SdlTexture::TextureDeleter> tex, int width, int height)
        : mTex{std::move(tex)}, mWidth{width}, mHeight{height} {
}

bool SdlTexture::isLoaded() const {
    return mTex != nullptr;
}

SDL_Texture* SdlTexture::getWrappedTexture() const {
    return mTex.get();
}

int SdlTexture::getWidth() const { return mWidth; }

int SdlTexture::getHeight() const { return mHeight; }

void SdlTexture::TextureDeleter::operator()(SDL_Texture* p) {
    SDL_DestroyTexture(p);
}
