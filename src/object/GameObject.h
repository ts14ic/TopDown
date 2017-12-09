#pragma once

#include "../utils/calculations.h"
#include "../assets/Assets.h"
#include <string>
#include <vector>

/* forward declarations begin */
struct SDL_Color;

class RenderContext;

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
    void default_move();

    void default_render(Assets& assets, RenderContext& renderContext);
};

bool objectsCollide(GameObject& a, GameObject& b);
