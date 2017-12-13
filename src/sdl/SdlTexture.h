//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../resources/Texture.h"
#include <memory>

class SDL_Texture;

class SdlTexture : public Texture {
public:
    struct TextureDeleter {
        void operator()(SDL_Texture* p);
    };

    SdlTexture();

    SdlTexture(std::unique_ptr<SDL_Texture, TextureDeleter> tex, int width, int height);

    SdlTexture(SdlTexture const&) = delete;

    SdlTexture(SdlTexture&&) noexcept;

    bool isLoaded() const override;

    int getWidth() const override;

    int getHeight() const override;

    SDL_Texture* getWrappedTexture() const;

private:
    std::unique_ptr<SDL_Texture, TextureDeleter> mTex;
    int mWidth = 0;
    int mHeight = 0;
};
