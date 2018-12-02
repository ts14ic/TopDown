#pragma once

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

    bool is_dying() const {
        return is_state(AI_DYING);
    }

    void set_state(AiState ai_state) {
        _ai_state = ai_state;
    }

private:
    AiState _ai_state = AI_IDLE;
};
