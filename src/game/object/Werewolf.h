#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <game/mixins/HasMeleeDamage.h>
#include <engine/random/Random.h>
#include <engine/audio/Audio.h>
#include <engine/Engine.h>
#include <vector>

class Werewolf : public Damageable, public HasMeleeDamage {
public:
    explicit Werewolf(Point2d<float> position);

    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

    Speed get_speed() const override { return _speed; }

    void set_speed(Speed speed) override { _speed = speed; }

    std::string get_tex_name() const override;

    // Damageable legacy
    Vitality get_vitality() const override { return _vitality; }

    void set_vitality(Vitality vitality) override { _vitality = vitality; }

    int get_melee_damage() const override;

    void take_damage(int damage_dealt) override;

    bool is_dead() const override;

    // StateMoon interface
    void set_target(Point2d<float> position);

    void teleport(Random& random);

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, Audio& audio,
                       float frames_count);

private:
    enum AiState {
        AI_IDLE = 0x0,
        AI_MOVING = 0x1,
        AI_ATTACKING = 0x2,
        AI_TELEPORTING = 0x4,
        AI_DYING = 0x8
    };

    Transform _transform;
    Speed _speed = Speed{2.5f};
    Vitality _vitality;
    int _animation_frame = 0;
    Timer _attack_cooldown;
    Timer _teleport_cooldown;
    int _ai_state = AI_IDLE;
};
