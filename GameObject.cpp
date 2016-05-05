#include "GameObject.h"
#include "sdlwrap.h"
#include <SDL_render.h>

void Damageable::default_render_health(SDL_Color const& c) const {
    if(hp() > 0) {
        SDL_Rect healthRect;
        healthRect.w = 50.f * hp() / defaultHp();
        healthRect.h = 5;
        healthRect.x = x() - healthRect.w / 2;
        healthRect.y = y() - circle().r;
        SDL_SetRenderDrawColor(renderer(), c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderer(), &healthRect);
    }
}
