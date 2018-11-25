#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <game/mixins/HasMeleeDamage.h>
#include <game/components/Sprite.h>
#include <game/components/WolfAi.h>
#include <engine/random/Random.h>
#include <engine/audio/Audio.h>
#include <engine/Engine.h>
#include <vector>

class Werewolf : public Damageable, public HasMeleeDamage {
public:
    explicit Werewolf(Point2<float> position);

    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

    Speed get_speed() const override { return _speed; }

    void set_speed(Speed speed) override { _speed = speed; }

    std::string get_tex_name() const override;

    // Damageable legacy
    Hitpoints get_hitpoints() const override { return _hitpoints; }

    void set_hitpoints(Hitpoints hitpoints) override { _hitpoints = hitpoints; }

    int get_melee_damage() const override;

    void take_damage(int damage_dealt) override;

    bool is_dead() const override;

    // StateMoon interface
    void set_target(Point2<float> position);

    void teleport(Random& random);

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, Audio& audio,
                       float frames_count);

private:
    Transform _transform;
    Speed _speed = Speed{2.5f};
    Hitpoints _hitpoints;
    Sprite _sprite;
    WolfAi _ai;
};
