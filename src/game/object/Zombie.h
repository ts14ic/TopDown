#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <engine/audio/Audio.h>
#include <engine/graphic/Graphic.h>
#include <vector>

class Zombie : public Damageable {
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

    bool is_dead() const override;

    int get_damage() const override;

    void damage(const Clock& clock, int damage_dealt) override;

    // StateMoon interface
    void set_target(Point2<float> position);

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, Audio& audio,
                       float frames_count);

private:
    Transform _transform;
    Speed _speed = Speed{1.7f};
    Hitpoints _hitpoints;

    int _animation_frame = 0;

    Timer _animation_timer;

    enum AiState {
        AI_IDLE = 0x0,
        AI_MOVING = 0x1,
        AI_ATTACKING = 0x2,
        AI_DYING = 0x4
    };
    int _ai_state = AI_IDLE;
};

std::vector<Zombie>& zombies();
