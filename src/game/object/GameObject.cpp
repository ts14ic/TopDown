#include "GameObject.h"
#include "../../engine/graphic/shape/Circle.h"
#include "../../engine/resources/Resources.h"
#include "../../engine/resources/Texture.h"
#include "../../engine/graphic/GraphicContext.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return circlesCollide(a.getCircle(), b.getCircle());
}

void GameObject::defaultMove() {
    setX(getX() + getCurrentSpeedX());
    setY(getY() + getCurrentSpeedY());
}

void GameObject::defaultRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio) {
    Texture& tex = resources.getTexture(getTexName());

    auto x = getX() - tex.getWidth() / 2;
    auto predictedDx = getCurrentSpeedX() * predictionRatio;

    auto y = getY() - tex.getHeight() / 2;
    auto predictedDy = getCurrentSpeedY() * predictionRatio;

    graphicContext.render(
            tex,
            static_cast<int>(x + predictedDx),
            static_cast<int>(y + predictedDy),
            getAngle()
    );
}
