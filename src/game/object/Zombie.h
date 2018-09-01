#pragma once

#include "Damageable.h"
#include "game/timer/Timer.h"
#include "engine/audio/Audio.h"
#include "engine/graphic/Graphic.h"
#include <vector>

class Zombie : public Damageable {
public:
    Zombie(int x, int y);

    // GameObject legacy
    Point2<float> get_position() const override { return _position; }

    using GameObject::set_position;

    void set_position(Point2<float> position) override { _position = position; }

    float get_angle() const override;

    void set_angle(float angle) override;

    float get_max_movement_speed() const override;

    void set_max_movement_speed(float speed) override;

    float get_current_x_speed() const override;

    void set_current_x_speed(float x_speed) override;

    float get_current_y_speed() const override;

    void set_current_y_speed(float y_speed) override;

    void set_current_speed(float x_speed, float y_speed) override;

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
    float _current_x_speed = 0.f;
    float _current_y_speed = 0.f;
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
