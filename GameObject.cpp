#include "GameObject.h"
#include "sdlwrap.h"
#include "EngineBase.h"

void Damageable::default_render_health(EngineBase& engine, SDL_Color const& c) const {
    if(hp() > 0) {
        SDL_Rect healthRect{};
        healthRect.w = static_cast<int>(50.f * hp() / defaultHp());
        healthRect.h = 5;
        healthRect.x = static_cast<int>(x() - healthRect.w / 2);
        healthRect.y = static_cast<int>(y() - circle().r);
        SDL_SetRenderDrawColor(engine.getRenderer(), c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(engine.getRenderer(), &healthRect);
    }
}
