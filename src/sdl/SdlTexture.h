//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../assets/Texture.h"
#include <memory>


class SdlTexture : public Texture {
public:
    SdlTexture();

    SdlTexture(RenderContext& engine, char const* path);

    SdlTexture(Texture const&) = delete;

    SdlTexture(Texture&&) = delete;

    void load(RenderContext& context, char const* path) override;

    bool isLoaded() const override;

    int getWidth() const override;

    int getHeight() const override;

    SDL_Texture* getWrapped() const override;

    struct FailedToLoadTextureException : public std::runtime_error {
        explicit FailedToLoadTextureException(const char* message);
    };

private:
    struct SDLTextureDeleter {
        void operator()(SDL_Texture* p);
    };

private:

    std::unique_ptr<SDL_Texture, SDLTextureDeleter> mTex;
    int mWidth = 0;
    int mHeight = 0;
};
