#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <engine/random/Random.h>
#include <engine/audio/Audio.h>
#include <vector>

class Werewolf : public Damageable {
public:
    explicit Werewolf(Point2<float> position);

    Point2<float> get_position() const override { return _position; }

    using GameObject::set_position;

    void set_position(Point2<float> position) override { _position = position; }

    float get_angle() const override;

    void set_angle(float a) override;

    float get_max_movement_speed() const override;

    void set_max_movement_speed(float s) override;

    Speed2<float> get_current_speed() const override { return _current_speed; }

    using GameObject::set_current_speed;

    void set_current_speed(Speed2<float> current_speed) override { _current_speed = current_speed; }

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    // Damageable legacy
    int get_hp() const override;

    int get_default_hp() const override;

    int get_damage() const override;

    void damage(const Clock& clock, int d) override;

    bool is_dead() const override;

    // StateMoon interface
    void set_target(const Clock& clock, Point2<float> position);

    void teleport(const Clock& clock, Random& random);

    void handle_logic(const Clock& clock);

    void handle_render(Engine& engine, Graphic& graphic_context, Audio& audio,
                       float frames_count);

private:
    Point2<float> _position;
    Speed2<float> _current_speed;
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
