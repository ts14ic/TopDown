#pragma once

#include "../Texture.h"
#include "../calculations.h"
#include <vector>

/* forward declarations begin */
struct SDL_Color;

/* forward declarations end */

class GameObject {
public:
    virtual float x() const = 0;

    virtual float y() const = 0;

    virtual float angle() const = 0;

    virtual float speed() const = 0;

    virtual void x(float v) = 0;

    virtual void y(float v) = 0;

    virtual void angle(float a) = 0;

    virtual void speed(float s) = 0;

    virtual Circle circle() const = 0;

    virtual std::string texName() const = 0;

protected:
    void default_move() {
        x(x() + speed() * dcos(angle()));
        y(y() + speed() * dsin(angle()));
    }

    void default_render(RenderSystem& engine) {
        Texture& tex = textures(texName());
        auto tx = static_cast<int>(x() - tex.w() / 2);
        auto ty = static_cast<int>(y() - tex.h() / 2);
        tex.render(engine, tx, ty, angle());
    }
};

bool objectsCollide(GameObject& a, GameObject& b);
