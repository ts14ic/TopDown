#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <game/components/ZombieAi.h>
#include <game/mixins/HasMeleeDamage.h>
#include <engine/audio/Audio.h>
#include <engine/graphic/Graphic.h>
#include <engine/Engine.h>
#include <vector>

class Zombie : public Damageable, public HasMeleeDamage {
public:
    explicit Zombie(Point2<float> position);

    // GameObject legacy
    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

    Speed get_speed() const override { return _speed; }

    void set_speed(Speed speed) override { _speed = speed; }

    std::string get_tex_name() const override;

    // Damageable legacy
    Hitpoints get_hitpoints() const override { return _hitpoints; }

    void set_hitpoints(Hitpoints hitpoints) override { _hitpoints = hitpoints; }

    bool is_dead() const override;

    int get_melee_damage() const override;

    void take_damage(const Clock& clock, int damage_dealt) override;

    // StateMoon interface
    void set_target(Point2<float> position);

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, Audio& audio,
                       float frames_count);

private:
    ZombieAi _zombie_ai;
    Transform _transform;
    Speed _speed = Speed{1.7f};
    Hitpoints _hitpoints;
    int _animation_frame = 0;
    Timer _animation_timer;
};
