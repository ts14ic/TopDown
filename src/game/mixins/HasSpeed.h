#pragma once

#include <game/components/Speed.h>

class HasSpeed {
public:
    virtual Speed get_speed() const = 0;

    virtual void set_speed(Speed speed) = 0;

    float get_max_movement_speed() const {
        return get_speed().max_speed;
    }

    void set_max_movement_speed(float max_speed) {
        Speed speed = get_speed();
        speed.max_speed = max_speed;
        set_speed(speed);
    }

    Speed2d<float> get_current_speed() const {
        return get_speed().current_speed;
    }

    void set_current_speed(Speed2d<float> current_speed) {
        Speed speed = get_speed();
        speed.current_speed = current_speed;
        set_speed(speed);
    }

    void set_current_speed(float x, float y) {
        set_current_speed(make_speed(x, y));
    }
};
