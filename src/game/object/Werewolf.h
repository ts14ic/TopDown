#pragma once

#include "Damageable.h"
#include <game/timer/Timer.h>
#include <engine/random/Random.h>
#include <engine/audio/Audio.h>
#include <vector>

class Werewolf : public Damageable {
public:
    explicit Werewolf(Point2<float> position);

    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

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
    Transform _transform;
    Speed2<float> _current_speed;
    float _max_movement_speed = 2.5f;

    int _current_hp;

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
