#include "GameObject.h"
#include "../utils/Circle.h"
#include "../assets/Assets.h"
#include "../engine/RenderContext.h"
#include "../utils/calculations.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return circlesCollide(a.circle(), b.circle());
}

void GameObject::default_move() {
    x(x() + speed() * cartesianCos(angle()));
    y(y() + speed() * cartesianSin(angle()));
}

void GameObject::default_render(Assets& assets, RenderContext& renderContext) {
    Texture& tex = assets.texture(texName());
    auto tx = static_cast<int>(x() - tex.getWidth() / 2);
    auto ty = static_cast<int>(y() - tex.getHeight() / 2);
    renderContext.render(tex, tx, ty, angle());
}
