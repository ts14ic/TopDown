#include "Damageable.h"

void Damageable::defaultRenderHealth(GraphicContext& graphicContext, Color const& color, float predictionRatio) const {
    if(hp() > 0) {
        Box healthBox;

        healthBox.setSize(50.f * hp() / defaultHp(), 5);
        healthBox.setPosition(
                getX() - healthBox.getWidth() / 2 + getCurrentSpeedX() * predictionRatio,
                getY() - getCircle().getRadius() + getCurrentSpeedY() * predictionRatio
        );

        graphicContext.renderBox(healthBox, color);
    }
}