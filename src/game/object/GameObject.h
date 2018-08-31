#pragma once

#include <string>

#include "engine/graphic/Circle.h"
#include "engine/Resources.h"
#include "engine/graphic/GraphicContext.h"

class GameObject {
public:
    virtual float get_x() const = 0;

    virtual float get_y() const = 0;

    virtual float get_angle() const = 0;

    virtual float get_max_movement_speed() const = 0;

    virtual float get_current_speed_x() const = 0;

    virtual float get_current_speed_y() const = 0;

    virtual Circle get_circle() const = 0;

    virtual std::string get_tex_name() const = 0;

    virtual void set_x(float x) = 0;

    virtual void set_y(float y) = 0;

    virtual void set_current_speed_x(float speedX) = 0;

    virtual void set_current_speed_y(float speedY) = 0;

    virtual void set_current_speed(float speedX, float speedY) = 0;

    virtual void set_position(float x, float y) = 0;

    virtual void set_angle(float angle) = 0;

    virtual void set_max_movement_speed(float speed) = 0;

protected:
    void default_move();

    void default_render(Resources &resources, GraphicContext &graphicContext, float predictionRatio);
};

bool objects_collide(GameObject &a, GameObject &b);
