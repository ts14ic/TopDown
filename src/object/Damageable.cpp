//
// Created by ts14ic on 12/3/17.
//
#include "Damageable.h"
#include "../shape/Circle.h"
#include "../math/math.h"
#include "../engine/GraphicContext.h"
#include "../shape/Box.h"

void Damageable::default_render_health(GraphicContext& graphicContext, Color const& color) const {
    if(hp() > 0) {
        Box healthBox;

        healthBox.setSize(50.f * hp() / defaultHp(), 5);
        healthBox.setPosition(getX() - healthBox.getWidth() / 2, getY() - getCircle().getRadius());

        graphicContext.renderBox(healthBox, color);
    }
}
