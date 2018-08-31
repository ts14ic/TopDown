#include "SdlGraphicContext.h"

SdlGraphicContext::SdlGraphicContext(SDL_Window* window, SDL_Renderer* renderer)
        : _window{window}, _renderer{renderer} {
}

void SdlGraphicContext::refresh_screen() {
    SDL_RenderPresent(_renderer);
}

void SdlGraphicContext::clear_screen() {
    SDL_RenderClear(_renderer);
}

void SdlGraphicContext::render(const Texture& texture, int x, int y) {
    if(texture.is_loaded()) {
        SDL_Rect destRect = {x, y, texture.get_width(), texture.get_height()};
        SDL_RenderCopy(_renderer, dynamic_cast<const SdlTexture &>(texture).get_wrapped_texture(), nullptr, &destRect);
    }
}

void SdlGraphicContext::render(Texture const& texture, int x, int y, float angle) {
    if(texture.is_loaded()) {
        SDL_Rect destRect = {x, y, texture.get_width(), texture.get_height()};
        SDL_RenderCopyEx(_renderer, dynamic_cast<const SdlTexture &>(texture).get_wrapped_texture(), nullptr,
                         &destRect,
                         angle, nullptr, SDL_FLIP_NONE);
    }
}

void SdlGraphicContext::render_box(const Box &box, const Color &color) {
    SDL_Rect rect{
            static_cast<int>(box.get_x()),
            static_cast<int>(box.get_y()),
            static_cast<int>(box.get_width()),
            static_cast<int>(box.get_height())
    };
    SDL_SetRenderDrawColor(
            _renderer,
            static_cast<Uint8>(color.get_red()),
            static_cast<Uint8>(color.get_green()),
            static_cast<Uint8>(color.get_blue()),
            static_cast<Uint8>(color.get_alpha())
    );
    SDL_RenderFillRect(_renderer, &rect);
}

int SdlGraphicContext::get_screen_width() {
    SDL_GetWindowSize(_window, &_screen_width, &_screen_height);
    return _screen_width;
}

int SdlGraphicContext::get_screen_height() {
    SDL_GetWindowSize(_window, &_screen_width, &_screen_height);
    return _screen_height;
}
