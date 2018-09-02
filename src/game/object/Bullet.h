#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include <engine/random/Random.h>
#include <vector>

class Bullet : public GameObject {
public:
    Bullet(Random& random, const GameObject& origin, const Weapon& weapon);

    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

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
    Transform _transform;
    Speed2<float> _current_speed;
    float _max_speed;
    int _damage;
};

std::vector<Bullet>& bullets();

