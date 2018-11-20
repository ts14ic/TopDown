#include "ZombieAnimation.h"

const ZombieAnimation::Animation ZombieAnimation::MOVING{
        "zombie", /*frame speeds: none*/{}, AnimationType::STATIC
};
const ZombieAnimation::Animation ZombieAnimation::ATTACKING{
        "zombie_attack", std::vector<std::size_t>(/*frames*/6, /*speed*/100), AnimationType::REPEATABLE
};
const ZombieAnimation::Animation ZombieAnimation::DYING{
        "zombie_death", std::vector<std::size_t>(/*frames*/7, /*speed*/500), AnimationType::ONESHOT
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return lhs.name == rhs.name;
}

bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return !(lhs == rhs);
}
