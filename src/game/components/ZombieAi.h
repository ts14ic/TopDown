#pragma once

class ZombieAi {
public:
    enum AiState {
        AI_IDLE = 0,
        AI_MOVING = 1 << 0,
        AI_ATTACKING = 1 << 1,
        AI_DYING = 1 << 2
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
