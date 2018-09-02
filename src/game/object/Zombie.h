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

    float get_max_movement_speed() const override;

    void set_max_movement_speed(float speed) override;

    Speed2<float> get_current_speed() const override { return _current_speed; }

    using GameObject::set_current_speed;

    void set_current_speed(Speed2<float> current_speed) override { _current_speed = current_speed; }

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    // Damageable legacy
    int get_hp() const override;

    int get_default_hp() const override;

    bool is_dead() const override;

    int get_damage() const override;

    void damage(const Clock& clock, int d) override;

    // StateMoon interface
    void set_target(Point2<float> position);

    void handle_logic();

    void handle_render(Engine& engine, Graphic& graphic, Audio& audio,
                       float frames_count);

private:
    Transform _transform;
    Speed2<float> _current_speed;
    float _speed = 1.7f;

    int _current_hp = 0;
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
