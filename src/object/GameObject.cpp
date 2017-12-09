#include "GameObject.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return ::collides(a.circle(), b.circle());
}

void GameObject::default_move() {
    x(x() + speed() * dcos(angle()));
    y(y() + speed() * dsin(angle()));
}

void GameObject::default_render(Assets& assets, RenderContext& engine) {
    Texture& tex = assets.texture(texName());
    auto tx = static_cast<int>(x() - tex.getWidth() / 2);
    auto ty = static_cast<int>(y() - tex.getHeight() / 2);
    tex.render(engine, tx, ty, angle());
}
