#pragma once

#include <game/timer/Timer.h>

class ZombieAi {
public:
    enum AiState {
        AI_IDLE = 0u,
        AI_MOVING = 1u,
        AI_ATTACKING = 1u << 1u,
        AI_DYING = 1u << 2u
    };

    bool is_state(AiState ai_state) const {
        return (_ai_state & ai_state) == ai_state;
    }

    bool is_moving() const {
        return is_state(AI_MOVING);
    }

    bool is_attacking() const {
        return is_state(AI_ATTACKING);
    }

    bool can_deal_damage() const {
        auto attack_time = _attack_cooldown.get_ticks_since_start();
        return attack_time >= 425 and attack_time <= 525;
    }

    bool must_reset_attack() const {
        return _attack_cooldown.ticks_passed_since_start(525);
    }

    void reset_attack() {
        _attack_cooldown.restart();
    }

    bool is_dying() const {
        return is_state(AI_DYING);
    }

    void set_state(AiState ai_state) {
        _ai_state = ai_state;
        _attack_cooldown.restart();
    }

private:
    AiState _ai_state = AI_IDLE;
    Timer _attack_cooldown;
};
