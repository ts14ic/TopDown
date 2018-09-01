#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include "engine/random/Random.h"
#include <vector>

class Bullet : public GameObject {
public:
    Bullet(Random& random, const GameObject& origin, const Weapon& weapon);

    Point2<float> get_position() const override { return _position; }

    Point2<float>& get_position() override { return _position; }

    float get_angle() const override;

    void set_angle(float a) override;

    float get_max_movement_speed() const override;

    void set_max_movement_speed(float s) override;

    float get_current_x_speed() const override;

    void set_current_x_speed(float x_speed) override;

    float get_current_y_speed() const override;

    void set_current_y_speed(float y_speed) override;

    void set_current_speed(float x_speed, float y_speed) override;

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    int get_damage() const;

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, float frames_count);

private:
    int _damage;
    Point2<float> _position;
    float _angle;
    float _max_speed;
    float _current_x_speed;
    float _current_y_speed;
};

std::vector<Bullet>& bullets();

