#include "ZombieAnimation.h"

const ZombieAnimation::Animation ZombieAnimation::MOVING{
        "zombie", /*frames*/0, /*speed*/0, AnimationType::STATIC
};
const ZombieAnimation::Animation ZombieAnimation::ATTACKING{
        "zombie_attack", /*frames*/6, /*speed*/100, AnimationType::REPEATABLE
};
const ZombieAnimation::Animation ZombieAnimation::DYING{
        "zombie_death", /*frames*/7, /*speed*/500, AnimationType::ONESHOT
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return lhs.name == rhs.name
           && lhs.frames == rhs.frames
           && lhs.speed == rhs.speed;
}

bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return !(lhs == rhs);
}
