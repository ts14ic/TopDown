#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <engine/random/Random.h>
#include <engine/audio/Audio.h>
#include <engine/Engine.h>
#include <vector>

class Werewolf : public Damageable {
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

    int get_damage() const override;

    void take_damage(const Clock& clock, int damage_dealt) override;

    bool is_dead() const override;

    // StateMoon interface
    void set_target(const Clock& clock, Point2<float> position);

    void teleport(const Clock& clock, Random& random);

    void handle_logic(const Clock& clock);

    void handle_render(Engine& engine, Graphic& graphic_context, Audio& audio,
                       float frames_count);

private:
    Transform _transform;
    Speed _speed = Speed{2.5f};
    Hitpoints _hitpoints;

    int _animation_frame = 0;
    Timer _attack_cooldown;
    Timer _teleport_cooldown;

    enum AiState {
        AI_IDLE = 0x0,
        AI_MOVING = 0x1,
        AI_ATTACKING = 0x2,
        AI_TELEPORTING = 0x4,
        AI_DYING = 0x8
    };
    int _ai_state = AI_IDLE;
};

std::vector<Werewolf>& werewolves();
