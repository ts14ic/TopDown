#pragma once

#include <game/components/Speed2d.h>

struct Speed {
    Speed() {
        max_speed = 0;
    }

    explicit Speed(float max_speed) {
        this->max_speed = max_speed;
    }

    Speed(Speed2d<float> current_speed, float max_speed) {
        this->current_speed = current_speed;
        this->max_speed = max_speed;
    }

    Speed2d<float> current_speed;
    float max_speed;
};
