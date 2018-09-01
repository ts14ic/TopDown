#pragma once

#include "Damageable.h"
#include "game/timer/Timer.h"
#include "engine/audio/AudioContext.h"
#include "engine/graphic/GraphicContext.h"
#include <vector>

class Zombie : public Damageable {
public:
    Zombie(int x, int y);

    // GameObject legacy
    float get_x() const override;

    float get_y() const override;

    float get_angle() const override;

    float get_max_movement_speed() const override;

    float get_current_speed_x() const override;

    float get_current_speed_y() const override;

    void set_x(float x) override;

    void set_y(float y) override;

    void set_position(float x, float y) override;

    void set_angle(float angle) override;

    void set_max_movement_speed(float speed) override;

    void set_current_speed_x(float speedX) override;

    void set_current_speed_y(float speedY) override;

    void set_current_speed(float speedX, float speedY) override;

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    // Damageable legacy
    int get_hp() const override;

    int get_default_hp() const override;

    bool is_dead() const override;

    int get_damage() const override;

    void damage(const Clock &clock, int d) override;

    // StateMoon interface
    void set_target(float x, float y);

    void handle_logic();

    void handle_render(Engine &resources, GraphicContext &graphicContext, AudioContext &audioContext,
                       float predictionRatio);

private:
    float _x = 0.f;
    float _y = 0.f;
    float _current_speed_x = 0.f;
    float _current_speed_y = 0.f;
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
