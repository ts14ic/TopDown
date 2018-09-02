#pragma once

#include <engine/geometry/Point2.h>

struct Transform {
    Transform() {
        angle = 0;
    }

    Transform(Point2<float> position, float rotation) {
        this->position = position;
        this->angle = rotation;
    }

    Point2<float> position;
    float angle;
};
