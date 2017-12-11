#include "Texture.h"
#include "../engine/RenderContext.h"
#include <SDL_image.h>

struct FailedToLoadTextureException : public std::runtime_error {
    explicit FailedToLoadTextureException(const char* message) : runtime_error(message) {}
};

Texture::Texture() = default;

Texture::Texture(RenderContext& engine, char const* path) {
    load(engine, path);
}

void Texture::load(RenderContext& engine, char const* path) {
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

    SDL_Log("Texture loaded: %s.\n", path);
    mTex.reset(newTex);
    mWidth = buf->w;
    mHeight = buf->h;
}

bool Texture::isLoaded() const {
    return mTex != nullptr;

}

SDL_Texture* Texture::getWrapped() const {
    return mTex.get();
}

void Texture::SDLTextureDeleter::operator()(SDL_Texture* p) {
    SDL_DestroyTexture(p);
}
