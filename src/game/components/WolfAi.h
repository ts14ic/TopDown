#pragma once

#include <game/timer/Timer.h>

class WolfAi {
public:
    enum AiState {
        AI_IDLE = 0x0,
        AI_MOVING = 0x1,
        AI_ATTACKING = 0x2,
        AI_TELEPORTING = 0x4,
        AI_DYING = 0x8
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

    bool can_attack_100() const {
        return _attack_cooldown.ticks_passed_since_start(100);
    }

    bool can_attack_600() const {
        return _attack_cooldown.ticks_passed_since_start(600);
    }

    void attack_restart() {
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

    void teleport_restart() {
        _teleport_cooldown.restart();
    }

    bool is_dying() const {
        return is_state(AI_DYING);
    }

    void set_state(AiState state) {
        _ai_state = state;
    }

private:
    Timer _attack_cooldown;
    Timer _teleport_cooldown;
    int _ai_state = AI_IDLE;
};
