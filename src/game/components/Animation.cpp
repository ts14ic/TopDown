#include "Animation.h"

const animation::State animation::ZOMBIE_MOVING{
        "zombie",
        /*frame durations: none*/{},
        animation::AnimationType::STATIC
};
const animation::State animation::ZOMBIE_ATTACKING{
        "zombie_attack",
        /*frame durations*/{150, 125, 100, 75, 50, 25},
        animation::AnimationType::REPEATABLE
};
const animation::State animation::ZOMBIE_DYING{
        "zombie_death",
        /*frame durations*/{75, 100, 130, 160, 190, 210, 240, 300},
        animation::AnimationType::ONESHOT
};

bool operator==(const animation::State& lhs, const animation::State& rhs) {
    return lhs.name == rhs.name;
}

bool operator!=(const animation::State& lhs, const animation::State& rhs) {
    return !(lhs == rhs);
}
