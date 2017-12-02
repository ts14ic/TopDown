#include "Texture.h"
#include "sdlwrap.h"
#include <SDL_image.h>
#include <unordered_map>

struct FailedToLoadTextureException : std::runtime_error {
    explicit FailedToLoadTextureException(const char *message) : runtime_error(message) {}
};

Texture::Texture() = default;

Texture::Texture(char const *path) {
    load(path);
}

void Texture::load(char const *path) {
    struct SDLSurfaceDeleter {
        void operator()(SDL_Surface *surf) {
            SDL_FreeSurface(surf);
        }
    };

    std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> buf{IMG_Load(path)};
    if(!buf) {
        throw FailedToLoadTextureException{IMG_GetError()};
    }

    SDL_Texture *newTex = SDL_CreateTextureFromSurface(renderer(), buf.get());
    if(!newTex) {
        throw FailedToLoadTextureException{SDL_GetError()};
    }

    SDL_Log("Loaded texture: %s.\n", path);
    mTex.reset(newTex);
    mWidth = buf->w;
    mHeight = buf->h;
}

void Texture::render(int x, int y) const {
    if(mTex) {
        SDL_Rect destRect = {x, y, mWidth, mHeight};
        SDL_RenderCopy(renderer(), mTex.get(), nullptr, &destRect);
    }
}

void Texture::render(int x, int y, float angle) const {
    if(mTex) {
        SDL_Rect destRect = {x, y, mWidth, mHeight};
        SDL_RenderCopyEx(renderer(), mTex.get(), nullptr, &destRect, angle, nullptr, SDL_FLIP_NONE);
    }
}

void Texture::render(int x, int y, float angle, int w, int h) const {
    if(mTex) {
        SDL_Rect dstRect = {x, y, w, h};
        SDL_Rect srcRect = {0, 0, w, h};
        SDL_RenderCopyEx(renderer(), mTex.get(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
    }
}

void Texture::render(SDL_Point const &pos) const {
    render(pos.x, pos.y);
}

void Texture::render(SDL_Point const &pos, float angle) const {
    render(pos.x, pos.y, angle);
}

void Texture::render(SDL_Point const &pos, float angle, SDL_Rect const &clip) const {
    render(pos.x, pos.y, angle, clip.w, clip.h);
}

void Texture::render(SDL_Point const &pos, SDL_Rect const &clip) const {
    if(mTex) {
        SDL_Rect dstRect = {pos.x, pos.y, clip.w, clip.h};
        SDL_Rect srcRect = {clip.x, clip.y, clip.w, clip.h};
        SDL_RenderCopy(renderer(), mTex.get(), &srcRect, &dstRect);
    }
}

Texture &textures(std::string const &name) {
    static std::unordered_map<std::string, Texture> ret;
    return ret[name];
}

void Texture::SDLTextureDeleter::operator()(SDL_Texture *p) {
    SDL_DestroyTexture(p);
}
