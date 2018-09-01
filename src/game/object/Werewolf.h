#pragma once

#include "Damageable.h"
#include "game/timer/Timer.h"
#include "engine/random/Random.h"
#include "engine/audio/Audio.h"
#include <vector>

class Werewolf : public Damageable {
public:
    Werewolf(float x, float y);

    // GameObject legacy
    float get_x() const override;

    float get_y() const override;

    float get_angle() const override;

    float get_max_movement_speed() const override;

    float get_current_x_speed() const override;

    float get_current_y_speed() const override;

    void set_x(float x) override;

    void set_y(float y) override;

    void set_position(float x, float y) override;

    void set_angle(float a) override;

    void set_max_movement_speed(float s) override;

    void set_current_x_speed(float x_speed) override;

    void set_current_y_speed(float y_speed) override;

    void set_current_speed(float x_speed, float y_speed) override;

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    // Damageable legacy
    int get_hp() const override;

    int get_default_hp() const override;

    int get_damage() const override;

    void damage(const Clock& clock, int d) override;

    bool is_dead() const override;

    // StateMoon interface
    void set_target(const Clock& clock, float x, float y);

    void teleport(const Clock& clock, Random& random);

    void handle_logic(const Clock& clock);

    void handle_render(Engine& engine, Graphic& graphic_context, Audio& audio,
                       float frames_count);

private:
    float _x = 0.f;
    float _y = 0.f;
    float _current_x_speed = 0.f;
    float _current_y_speed = 0.f;
    float _max_movement_speed = 2.5f;
    float _view_angle = 0.f;

    int _current_hp;

    int _animation_frame = 0;
    Timer _attack_cooldown;
    Timer _teleport_cooldown;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        TELEPORTING = 0x4,
        DYING = 0x8
    };
    int _ai_state = IDLE;
};

std::vector<Werewolf>& werewolves();
