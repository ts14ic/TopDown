#include "ZombieAnimation.h"

const ZombieAnimation::Animation ZombieAnimation::MOVING{
        "zombie",
        /*frame speeds: none*/{},
        AnimationType::STATIC
};
const ZombieAnimation::Animation ZombieAnimation::ATTACKING{
        "zombie_attack",
        /*frame speeds*/{150, 125, 100, 75, 50, 25},
        AnimationType::REPEATABLE
};
const ZombieAnimation::Animation ZombieAnimation::DYING{
        "zombie_death",
        /*frame speeds*/{75, 100, 130, 160, 190, 210, 240, 300},
        AnimationType::ONESHOT
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return lhs.name == rhs.name;
}

bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return !(lhs == rhs);
}
