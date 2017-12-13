#include "GameObject.h"
#include "../shape/Circle.h"
#include "../assets/Assets.h"
#include "../assets/Texture.h"
#include "../engine/GraphicContext.h"
#include "../math/math.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return circlesCollide(a.getCircle(), b.getCircle());
}

void GameObject::default_move() {
    setX(getX() + getSpeed() * cartesianCos(getAngle()));
    setY(getY() + getSpeed() * cartesianSin(getAngle()));
}

void GameObject::default_render(Assets& assets, GraphicContext& graphicContext) {
    Texture& tex = assets.getTexture(getTexName());
    auto tx = static_cast<int>(getX() - tex.getWidth() / 2);
    auto ty = static_cast<int>(getY() - tex.getHeight() / 2);
    graphicContext.render(tex, tx, ty, getAngle());
}
