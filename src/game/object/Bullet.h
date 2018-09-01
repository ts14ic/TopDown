#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include "engine/random/Random.h"
#include <vector>

class Bullet : public GameObject {
public:
    Bullet(Random& random, const GameObject& origin, const Weapon& weapon);

    Point2<float> get_position() const override { return _position; }

    using GameObject::set_position;

    void set_position(Point2<float> position) override { _position = position; }

    float get_angle() const override;

    void set_angle(float a) override;

    float get_max_movement_speed() const override;

    void set_max_movement_speed(float s) override;

    Speed2<float> get_current_speed() const override { return _current_speed; }

    using GameObject::set_current_speed;

    void set_current_speed(Speed2<float> current_speed) override { _current_speed = current_speed; }

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    int get_damage() const;

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, float frames_count);

private:
    int _damage;
    Point2<float> _position;
    Speed2<float> _current_speed;
    float _angle;
    float _max_speed;
};

std::vector<Bullet>& bullets();

