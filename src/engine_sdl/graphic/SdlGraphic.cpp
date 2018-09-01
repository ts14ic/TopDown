#include "SdlGraphic.h"
#include "engine_sdl/SdlEngine.h"
#include <SDL_image.h>
#include <SDL.h>

SdlGraphic::SdlGraphic(int screen_width, int screen_height) {
    _window.reset(SDL_CreateWindow(
            "TopDown - Reborn",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            screen_width, screen_height,
            SDL_WINDOW_SHOWN
    ));
    if (_window == nullptr) {
        throw SdlEngine::FailedSdlInitException{SDL_GetError()};
    }

    _renderer.reset(SDL_CreateRenderer(
            _window.get(), -1,
            SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC
    ));
    if (_renderer == nullptr) {
        throw SdlEngine::FailedSdlInitException{SDL_GetError()};
    }

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        throw SdlEngine::FailedSdlInitException{IMG_GetError()};
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_SetRenderDrawColor(_renderer.get(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(_renderer.get());
    SDL_RenderPresent(_renderer.get());
}

SdlGraphic::~SdlGraphic() {
    _name_to_texture.clear();
    IMG_Quit();
}

void SdlGraphic::SdlDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void SdlGraphic::SdlDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}


void SdlGraphic::refresh_screen() {
    SDL_RenderPresent(_renderer.get());
}

void SdlGraphic::clear_screen() {
    SDL_RenderClear(_renderer.get());
}

void SdlGraphic::render(const SdlTexture& texture, int x, int y) {
    if (texture.is_loaded()) {
        SDL_Rect destRect = {x, y, texture.get_width(), texture.get_height()};
        SDL_RenderCopy(_renderer.get(), texture.get_wrapped_texture(), nullptr,
                       &destRect);
    }
}

void SdlGraphic::render(const SdlTexture& texture, int x, int y, float angle) {
    if (texture.is_loaded()) {
        SDL_Rect destRect = {x, y, texture.get_width(), texture.get_height()};
        SDL_RenderCopyEx(_renderer.get(), texture.get_wrapped_texture(), nullptr,
                         &destRect,
                         angle, nullptr, SDL_FLIP_NONE);
    }
}

void SdlGraphic::render_box(const Box& box, const Color& color) {
    SDL_Rect rect{
            static_cast<int>(box.get_x()),
            static_cast<int>(box.get_y()),
            static_cast<int>(box.get_width()),
            static_cast<int>(box.get_height())
    };
    SDL_SetRenderDrawColor(
            _renderer.get(),
            static_cast<Uint8>(color.get_red()),
            static_cast<Uint8>(color.get_green()),
            static_cast<Uint8>(color.get_blue()),
            static_cast<Uint8>(color.get_alpha())
    );
    SDL_RenderFillRect(_renderer.get(), &rect);
}

int SdlGraphic::get_screen_width() {
    int _screen_width, _;
    SDL_GetWindowSize(_window.get(), &_screen_width, &_);
    return _screen_width;
}

int SdlGraphic::get_screen_height() {
    int _, _screen_height;
    SDL_GetWindowSize(_window.get(), &_, &_screen_height);
    return _screen_height;
}

struct SurfaceDeleter {
    void operator()(SDL_Surface* surf) {
        SDL_FreeSurface(surf);
    }
};

using SurfaceHandle = std::unique_ptr<SDL_Surface, SurfaceDeleter>;

SdlTexture SdlGraphic::load_texture(const char* path) {
    SurfaceHandle surface_handle{IMG_Load(path)};
    if (surface_handle == nullptr) {
        throw FailedToLoadTextureException{IMG_GetError()};
    }

    TextureHandle texture_handle{SDL_CreateTextureFromSurface(_renderer.get(), surface_handle.get())};
    if (texture_handle == nullptr) {
        throw FailedToLoadTextureException{SDL_GetError()};
    }

    SdlTexture tex{std::move(texture_handle), surface_handle->w, surface_handle->h};
    SDL_Log("SdlTexture loaded: %s.\n", path);
    return tex;
}

Texture SdlGraphic::get_texture(const std::string& name) {
    SdlTexture& sdl_texture = _name_to_texture[name];
    return Texture{name, sdl_texture.get_width(), sdl_texture.get_height()};
}

void SdlGraphic::load_texture(const std::string& name, const char* path) {
    _name_to_texture.insert(std::make_pair(name, load_texture(path)));
}

void SdlGraphic::render_texture(const std::string& texture_name, int x, int y) {
    render(_name_to_texture[texture_name], x, y);
}

void SdlGraphic::render_texture(const std::string& texture_name, int x, int y, float angle) {
    render(_name_to_texture[texture_name], x, y, angle);
}

SdlGraphic::FailedToLoadTextureException::FailedToLoadTextureException(const char* message)
        : runtime_error(message) {}
