#include "GameObject.h"
#include "../shape/Circle.h"
#include "../resources/Resources.h"
#include "../resources/Texture.h"
#include "../engine/GraphicContext.h"
#include "../math/math.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return circlesCollide(a.getCircle(), b.getCircle());
}

void GameObject::default_move() {
    setX(getX() + getMaxMovementSpeed() * cartesianCos(getAngle()));
    setY(getY() + getMaxMovementSpeed() * cartesianSin(getAngle()));
}

void GameObject::defaultRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio) {
    Texture& tex = resources.getTexture(getTexName());

    // TODO Use current x and y speeds instead of getMovementSpeed

    auto x = getX() - tex.getWidth() / 2;
    auto predictedDx = getMaxMovementSpeed() * cartesianCos(getAngle()) * predictionRatio;

    auto y = getY() - tex.getHeight() / 2;
    auto predictedDy = getMaxMovementSpeed() * cartesianSin(getAngle()) * predictionRatio;

    graphicContext.render(
            tex,
            static_cast<int>(x + predictedDx),
            static_cast<int>(y + predictedDy),
            getAngle()
    );
}
