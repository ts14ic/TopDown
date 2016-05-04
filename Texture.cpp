#include "Texture.h"
#include "sdlwrap.h"
#include <SDL_image.h>
#include <SDL_render.h>
#include <memory>
#include <unordered_map>

Texture::Texture()
{}

Texture::Texture(char const* path) {
    load(path);
}

void Texture::load(char const* path) {
    SDL_Surface* buf = IMG_Load(path);
    if(!buf) {
        SDL_Log("Failed loading %s. %s.\n", path, IMG_GetError());
        throw FailedToLoadTextureException();
    }
    
    SDL_Texture* newTex = SDL_CreateTextureFromSurface(renderer(), buf);
    if(!newTex) {
        SDL_Log("Failed creating texture %s. %s.\n", path, SDL_GetError());
        SDL_FreeSurface(buf);
        throw FailedToLoadTextureException();
    }
    
    SDL_Log("Loaded texture: %s.\n", path);
    if(_tex) SDL_DestroyTexture(_tex);
    _tex = newTex;
    _w = buf->w;
    _h = buf->h;
    SDL_FreeSurface(buf);
}

Texture::~Texture() {
    if(_tex) {
        SDL_DestroyTexture(_tex);
    }
}

void Texture::render(int x, int y) const {
    if(!_tex) return;
    
    SDL_Rect dstrect = {x, y, _w, _h};
    SDL_RenderCopy(renderer(), _tex, nullptr, &dstrect);
}

void Texture::render(int x, int y, float angle) const {
    if(!_tex) return;
    
    SDL_Rect dstrect = {x, y, _w, _h};
    SDL_RenderCopyEx(renderer(), _tex, nullptr, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}

void Texture::render(int x, int y, float angle, int w, int h) const {
    if(!_tex) return;
    
    SDL_Rect dstrect = {x, y, w, h};
    SDL_Rect srcrect = {0, 0, w, h};
    SDL_RenderCopyEx(renderer(), _tex, &srcrect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
}

void Texture::render(SDL_Point const& pos) const {
    render(pos.x, pos.y);
}

void Texture::render(SDL_Point const& pos, float angle) const {
    render(pos.x, pos.y, angle);
}

void Texture::render(SDL_Point const& pos, float angle, SDL_Rect const& clip) const {
    render(pos.x, pos.y, angle, clip.w, clip.h);
}

void Texture::render(SDL_Point const& pos, SDL_Rect const& clip) const {
    SDL_Rect dstrect = {pos.x, pos.y, clip.w, clip.h};
    SDL_Rect srcrect = {clip.x, clip.y, clip.w, clip.h};
    SDL_RenderCopy(renderer(), _tex, &srcrect, &dstrect);
}

Texture& textures(std::string const& name) {
    static std::unordered_map<std::string, Texture> ret;
    return ret[name];
}
