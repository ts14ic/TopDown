#include "ZombieAnimation.h"

const ZombieAnimation::Animation ZombieAnimation::MOVING{
        "zombie", /*frames*/0, /*speed*/0
};
const ZombieAnimation::Animation ZombieAnimation::ATTACKING{
        "zombie_attack", /*frames*/6, /*speed*/100
};
const ZombieAnimation::Animation ZombieAnimation::DYING{
        "zombie_death", /*frames*/7, /*speed*/500
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return lhs.name == rhs.name
           && lhs.frames == rhs.frames
           && lhs.speed == rhs.speed;
}

bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs) {
    return !(lhs == rhs);
}
