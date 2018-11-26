#pragma once

#include "GameObject.h"
#include <game/mixins/HasVitality.h>
#include <engine/clock/Clock.h>
#include <engine/geometry/Color.h>

class Damageable : public virtual GameObject, public HasVitality {
public:
    virtual void take_damage(int damageAmount) = 0;

    virtual bool is_dead() const = 0;

protected:
    void default_render_health(Graphic& graphic, const Color& color, float frames_count) const;
};
