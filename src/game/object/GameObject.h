#pragma once

#include <string>

class Circle;

class Resources;

class GraphicContext;

class GameObject {
public:
    virtual float getX() const = 0;

    virtual float getY() const = 0;

    virtual float getAngle() const = 0;

    virtual float getMaxMovementSpeed() const = 0;

    virtual float getCurrentSpeedX() const = 0;

    virtual float getCurrentSpeedY() const = 0;

    virtual Circle getCircle() const = 0;

    virtual std::string getTexName() const = 0;

    virtual void setX(float x) = 0;

    virtual void setY(float y) = 0;

    virtual void setCurrentSpeedX(float speedX) = 0;

    virtual void setCurrentSpeedY(float speedY) = 0;

    virtual void setCurrentSpeed(float speedX, float speedY) = 0;

    virtual void setPos(float x, float y) = 0;

    virtual void setAngle(float angle) = 0;

    virtual void setMaxMovementSpeed(float speed) = 0;

protected:
    void defaultMove();

    void defaultRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio);
};

bool objectsCollide(GameObject& a, GameObject& b);
