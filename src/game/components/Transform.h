#pragma once

#include <engine/geometry/Point2d.h>
#include <engine/geometry/Circle.h>

struct Transform {
    Transform() {
        angle = 0;
        radius = 0;
    }

    Transform(Point2d<float> position, float rotation, float radius) {
        this->position = position;
        this->angle = rotation;
        this->radius = radius;
    }

    Circle get_circle() const {
        return Circle{position, radius};
    }

    Point2d<float> position;
    float angle;
    float radius;
};
