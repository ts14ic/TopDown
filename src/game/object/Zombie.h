#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <game/components/ZombieAi.h>
#include <game/mixins/HasMeleeDamage.h>
#include <engine/audio/Audio.h>
#include <engine/graphic/Graphic.h>
#include <engine/Engine.h>
#include <vector>
#include <game/components/Sprite.h>

class Zombie : public Damageable, public HasMeleeDamage {
public:
    explicit Zombie(Point2d<float> position);

    // GameObject legacy
    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

    Speed get_speed() const override { return _speed; }

    void set_speed(Speed speed) override { _speed = speed; }

    std::string get_tex_name() const override;

    // Damageable legacy
    Vitality get_vitality() const override { return _vitality; }

    void set_vitality(Vitality vitality) override { _vitality = vitality; }

    bool is_dead() const override;

    int get_melee_damage() const override;

    void take_damage(int damage_dealt) override;

    // StateMoon interface
    void set_target(Point2d<float> position);

    void handle_logic();

    void handle_render(Engine& engine, float frames_count);

private:
    Transform _transform;
    Speed _speed = Speed{1.7f};
    Vitality _vitality;
    ZombieAi _ai;
    Sprite _sprite;
};
