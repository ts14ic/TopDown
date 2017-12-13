#include "GameObject.h"
#include "../shape/Circle.h"
#include "../assets/Assets.h"
#include "../texture/Texture.h"
#include "../engine/RenderContext.h"
#include "../math/math.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return circlesCollide(a.getCircle(), b.getCircle());
}

void GameObject::default_move() {
    setX(getX() + getSpeed() * cartesianCos(getAngle()));
    setY(getY() + getSpeed() * cartesianSin(getAngle()));
}

void GameObject::default_render(Assets& assets, RenderContext& renderContext) {
    Texture& tex = assets.texture(getTexName());
    auto tx = static_cast<int>(getX() - tex.getWidth() / 2);
    auto ty = static_cast<int>(getY() - tex.getHeight() / 2);
    renderContext.render(tex, tx, ty, getAngle());
}
