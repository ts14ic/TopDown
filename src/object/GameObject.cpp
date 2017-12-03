#include "GameObject.h"
#include "../texture/Texture.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return ::collides(a.circle(), b.circle());
}

void GameObject::default_move() {
    x(x() + speed() * dcos(angle()));
    y(y() + speed() * dsin(angle()));
}

void GameObject::default_render(RenderContext& engine) {
    Texture& tex = textures(texName());
    auto tx = static_cast<int>(x() - tex.w() / 2);
    auto ty = static_cast<int>(y() - tex.h() / 2);
    tex.render(engine, tx, ty, angle());
}
