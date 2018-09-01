#pragma once

#include "Damageable.h"
#include "game/timer/Timer.h"
#include "engine/audio/Audio.h"
#include "engine/graphic/Graphic.h"
#include <vector>

class Zombie : public Damageable {
public:
    explicit Zombie(Point2<float> position);

    // GameObject legacy
    Point2<float> get_position() const override { return _position; }

    using GameObject::set_position;

    void set_position(Point2<float> position) override { _position = position; }

    float get_angle() const override;

    void set_angle(float angle) override;

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
    Point2<float> _position;
    Speed2<float> _current_speed;
    float _angle = 0.f;
    float _speed = 1.7f;

    int _current_hp = 0;
    int _animation_frame = 0;

    Timer _animation_timer;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        DYING = 0x4
    };
    int _ai_state = IDLE;
};

std::vector<Zombie>& zombies();
