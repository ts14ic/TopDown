#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include "engine/random/Random.h"
#include <vector>

class Bullet : public GameObject {
public:
    Bullet(Random& random, GameObject const& origin, Weapon const& weapon);

    float get_x() const override;

    float get_y() const override;

    float get_angle() const override;

    float get_max_movement_speed() const override;

    float get_current_speed_x() const override;

    float get_current_speed_y() const override;

    void set_x(float x) override;

    void set_y(float y) override;

    void set_position(float x, float y) override;

    void set_angle(float a) override;

    void set_max_movement_speed(float s) override;

    void set_current_speed_x(float speedX) override;

    void set_current_speed_y(float speedY) override;

    void set_current_speed(float speedX, float speedY) override;

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    int get_damage() const;

    void handle_logic();

    void handle_render(Resources &resources, GraphicContext &graphicContext, float predictionRatio);

private:
    int _damage;
    float _x;
    float _y;
    float _angle;
    float _max_speed;
    float _current_speed_x;
    float _current_speed_y;
};

std::vector<Bullet>& bullets();

