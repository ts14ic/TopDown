#pragma once

#include <string>
#include <vector>

class Circle;

class Resources;

class GraphicContext;

class GameObject {
public:
    virtual float getX() const = 0;

    virtual float getY() const = 0;

    virtual float getAngle() const = 0;

    // TODO Add getters for x y speeds
    virtual float getMaxMovementSpeed() const = 0;

    virtual Circle getCircle() const = 0;

    virtual std::string getTexName() const = 0;

    virtual void setX(float x) = 0;

    virtual void setY(float y) = 0;

    virtual void setPos(float x, float y) = 0;

    virtual void setAngle(float angle) = 0;

    virtual void setSpeed(float speed) = 0;

protected:
    void default_move();

    void defaultRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio);
};

bool objectsCollide(GameObject& a, GameObject& b);
