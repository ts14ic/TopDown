#pragma once

#include <game/components/Transform.h>
#include <engine/geometry/Circle.h>

class HasTransform {
public:
    virtual Transform get_transform() const = 0;

    virtual void set_transform(Transform transform) = 0;

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
};