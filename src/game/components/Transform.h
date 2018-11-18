#pragma once

#include <engine/geometry/Point2.h>
#include <engine/geometry/Circle.h>

struct Transform {
    Transform() {
        angle = 0;
        radius = 0;
    }

    Transform(Point2<float> position, float rotation, float radius) {
        this->position = position;
        this->angle = rotation;
        this->radius = radius;
    }

    Circle get_circle() const {
        return Circle{position, radius};
    }

    Point2<float> position;
    float angle;
    float radius;
};
