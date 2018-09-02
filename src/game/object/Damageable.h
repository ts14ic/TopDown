#pragma once

#include "GameObject.h"
#include "HasHitpoints.h"
#include <engine/clock/Clock.h>
#include <engine/geometry/Color.h>

class Damageable : public virtual GameObject, public HasHitpoints {
public:
    virtual int get_damage() const = 0;

    virtual void damage(const Clock& clock, int damageAmount) = 0;

    virtual bool is_dead() const = 0;

protected:
    void default_render_health(Graphic& graphic_context, const Color& color, float frames_count) const;
};
