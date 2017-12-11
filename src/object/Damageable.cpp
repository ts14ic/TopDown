//
// Created by ts14ic on 12/3/17.
//
#include "Damageable.h"
#include "../shape/Circle.h"
#include "../math/math.h"
#include "../engine/RenderContext.h"
#include <SDL_video.h>
#include <SDL_render.h>

void Damageable::default_render_health(RenderContext& renderContext, SDL_Color const& c) const {
    if(hp() > 0) {
        SDL_Rect healthRect{};
        healthRect.w = static_cast<int>(50.f * hp() / defaultHp());
        healthRect.h = 5;
        healthRect.x = static_cast<int>(getX() - healthRect.w / 2);
        healthRect.y = static_cast<int>(getY() - getCircle().getRadius());
        SDL_SetRenderDrawColor(renderContext.getRenderer(), c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderContext.getRenderer(), &healthRect);
    }
}
