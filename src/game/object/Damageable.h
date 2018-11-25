#pragma once

#include "GameObject.h"
#include <game/mixins/HasHitpoints.h>
#include <engine/clock/Clock.h>
#include <engine/geometry/Color.h>

class Damageable : public virtual GameObject, public HasHitpoints {
public:
    virtual void take_damage(int damageAmount) = 0;

    virtual bool is_dead() const = 0;
};
