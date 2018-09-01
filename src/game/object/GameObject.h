#pragma once

#include <string>

#include "engine/graphic/Circle.h"
#include "engine/Engine.h"
#include "engine/graphic/Graphic.h"

class GameObject {
public:
    virtual float get_x() const = 0;

    virtual float get_y() const = 0;

    virtual float get_angle() const = 0;

    virtual float get_max_movement_speed() const = 0;

    virtual float get_current_x_speed() const = 0;

    virtual float get_current_y_speed() const = 0;

    virtual Circle get_circle() const = 0;

    virtual std::string get_tex_name() const = 0;

    virtual void set_x(float x) = 0;

    virtual void set_y(float y) = 0;

    virtual void set_current_x_speed(float x_speed) = 0;

    virtual void set_current_y_speed(float y_speed) = 0;

    virtual void set_current_speed(float x_speed, float y_speed) = 0;

    virtual void set_position(float x, float y) = 0;

    virtual void set_angle(float angle) = 0;

    virtual void set_max_movement_speed(float speed) = 0;

protected:
    void default_move();

    void default_render(Graphic& graphic, float frames_count);
};

bool objects_collide(GameObject& a, GameObject& b);
