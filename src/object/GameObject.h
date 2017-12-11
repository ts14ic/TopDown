#pragma once

#include <string>
#include <vector>

struct SDL_Color;

class Circle;
class Assets;
class RenderContext;

class GameObject {
public:
    virtual float getX() const = 0;

    virtual float getY() const = 0;

    virtual void setPos(float x, float y) = 0;

    virtual float getAngle() const = 0;

    virtual float getSpeed() const = 0;

    virtual void setX(float x) = 0;

    virtual void setY(float y) = 0;

    virtual void setAngle(float angle) = 0;

    virtual void setSpeed(float speed) = 0;

    virtual Circle getCircle() const = 0;

    virtual std::string getTexName() const = 0;

protected:
    void default_move();

    void default_render(Assets& assets, RenderContext& renderContext);
};

bool objectsCollide(GameObject& a, GameObject& b);
