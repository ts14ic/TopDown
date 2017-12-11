//
// Created by ts14ic on 12/3/17.
//
#include "Damageable.h"
#include "../utils/Circle.h"
#include "../utils/calculations.h"
#include "../engine/RenderContext.h"
#include <SDL_video.h>
#include <SDL_render.h>

void Damageable::default_render_health(RenderContext& renderContext, SDL_Color const& c) const {
    if(hp() > 0) {
        SDL_Rect healthRect{};
        healthRect.w = static_cast<int>(50.f * hp() / defaultHp());
        healthRect.h = 5;
        healthRect.x = static_cast<int>(x() - healthRect.w / 2);
        healthRect.y = static_cast<int>(y() - circle().getRadius());
        SDL_SetRenderDrawColor(renderContext.getRenderer(), c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderContext.getRenderer(), &healthRect);
    }
}
