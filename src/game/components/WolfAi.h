#pragma once

#include <game/timer/Timer.h>

class WolfAi {
public:
    enum AiState {
        AI_IDLE = 0,
        AI_MOVING = 1u,
        AI_ATTACKING = 1u << 1u,
        AI_TELEPORTING = 1u << 2u,
        AI_DYING = 1u << 3u
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
        return (attack_time >= 300 and attack_time < 400) or (attack_time >= 700 and attack_time < 800);
    }

    bool must_reset_attack() const {
        return _attack_cooldown.ticks_passed_since_start(800);
    }

    void restart_attack() {
        _attack_cooldown.restart();
    }

    bool is_teleporting() const {
        return is_state(AI_TELEPORTING);
    }

    bool teleport_finished() const {
        return _teleport_cooldown.ticks_passed_since_start(500);
    }

    bool can_teleport() const {
        return _teleport_cooldown.ticks_passed_since_start(1000);
    }

    void restart_teleport() {
        _teleport_cooldown.restart();
    }

    bool is_dying() const {
        return is_state(AI_DYING);
    }

    void set_state(AiState state) {
        _ai_state = state;
        _attack_cooldown.restart();
        _teleport_cooldown.restart();
    }

private:
    Timer _attack_cooldown;
    Timer _teleport_cooldown;
    AiState _ai_state = AI_IDLE;
};
