//
// Created by ts14ic on 12/13/17.
//

#include "SdlTexture.h"
#include "../engine/RenderContext.h"
#include <SDL_image.h>

SdlTexture::FailedToLoadTextureException::FailedToLoadTextureException(const char* message)
        : runtime_error(message) {}

SdlTexture::SdlTexture() = default;

SdlTexture::SdlTexture(RenderContext& engine, char const* path) {
    load(engine, path);
}

void SdlTexture::load(RenderContext& engine, char const* path) {
    struct SDLSurfaceDeleter {
        void operator()(SDL_Surface* surf) {
            SDL_FreeSurface(surf);
        }
    };

    std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> buf{IMG_Load(path)};
    if(!buf) {
        throw FailedToLoadTextureException{IMG_GetError()};
    }

    SDL_Texture* newTex = SDL_CreateTextureFromSurface(engine.getRenderer(), buf.get());
    if(!newTex) {
        throw FailedToLoadTextureException{SDL_GetError()};
    }

    SDL_Log("SdlTexture loaded: %s.\n", path);
    mTex.reset(newTex);
    mWidth = buf->w;
    mHeight = buf->h;
}

bool SdlTexture::isLoaded() const {
    return mTex != nullptr;

}

SDL_Texture* SdlTexture::getWrapped() const {
    return mTex.get();
}

int SdlTexture::getWidth() const { return mWidth; }

int SdlTexture::getHeight() const { return mHeight; }

void SdlTexture::SDLTextureDeleter::operator()(SDL_Texture* p) {
    SDL_DestroyTexture(p);
}
