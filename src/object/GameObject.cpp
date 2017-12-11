#include "GameObject.h"
#include "../assets/Assets.h"
#include "../utils/calculations.h"
#include "../engine/RenderContext.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return ::collides(a.circle(), b.circle());
}

void GameObject::default_move() {
    x(x() + speed() * dcos(angle()));
    y(y() + speed() * dsin(angle()));
}

void GameObject::default_render(Assets& assets, RenderContext& renderContext) {
    Texture& tex = assets.texture(texName());
    auto tx = static_cast<int>(x() - tex.getWidth() / 2);
    auto ty = static_cast<int>(y() - tex.getHeight() / 2);
    renderContext.render(tex, tx, ty, angle());
}
