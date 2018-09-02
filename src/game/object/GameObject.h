#pragma once

#include <string>

#include <game/components/Transform.h>
#include <game/components/Speed.h>
#include <engine/geometry/Circle.h>
#include <engine/Engine.h>
#include <engine/graphic/Graphic.h>
#include <engine/geometry/Point2.h>

class GameObject {
public:
    virtual Transform get_transform() const = 0;

    virtual void set_transform(Transform transform) = 0;

    virtual Speed get_speed() const = 0;

    virtual void set_speed(Speed speed) = 0;

    virtual std::string get_tex_name() const = 0;

    Point2<float> get_position() const {
        return get_transform().position;
    }

    void set_position(Point2<float> position) {
        Transform transform = get_transform();
        transform.position = position;
        set_transform(transform);
    }

    void set_position(float x, float y) {
        set_position(make_point(x, y));
    }

    void set_x(float x) {
        auto position = get_position();
        position.x = x;
        set_position(position);
    }

    void set_y(float y) {
        auto position = get_position();
        position.y = y;
        set_position(position);
    }

    float get_angle() const {
        return get_transform().angle;
    }

    void set_angle(float angle) {
        Transform transform = get_transform();
        transform.angle = angle;
        set_transform(transform);
    }

    Circle get_circle() const {
        Transform transform = get_transform();
        return Circle{transform.position, transform.radius};
    }

    float get_max_movement_speed() const {
        return get_speed().max_speed;
    }

    void set_max_movement_speed(float max_speed) {
        Speed speed = get_speed();
        speed.max_speed = max_speed;
        set_speed(speed);
    }

    Speed2<float> get_current_speed() const {
        return get_speed().current_speed;
    }

    void set_current_speed(Speed2<float> current_speed) {
        Speed speed = get_speed();
        speed.current_speed = current_speed;
        set_speed(speed);
    }

    void set_current_speed(float x, float y) {
        set_current_speed(make_speed(x, y));
    }

protected:
    void default_move();

    void default_render(Graphic& graphic, float frames_count);
};

bool objects_collide(GameObject& a, GameObject& b);
