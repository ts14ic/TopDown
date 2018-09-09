#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include <game/mixins/HasMeleeDamage.h>
#include <engine/random/Random.h>
#include <vector>

class Bullet : public virtual GameObject, public HasMeleeDamage {
public:
    Bullet(Random& random, const GameObject& origin, const Weapon& weapon);

    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

    Speed get_speed() const override { return _speed; }

    void set_speed(Speed speed) override { _speed = speed; }

    std::string get_tex_name() const override;

    int get_melee_damage() const override;

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, float frames_count);

private:
    Transform _transform;
    Speed _speed;
    int _damage;
};

std::vector<Bullet>& bullets();

