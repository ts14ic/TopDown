#pragma once

#include "GameObject.h"
#include <game/components/Hitpoints.h>
#include <engine/clock/Clock.h>
#include <engine/geometry/Color.h>

class Damageable : public virtual GameObject {
public:
    virtual Hitpoints get_hitpoints() const = 0;

    int get_hp() const { return get_hitpoints().current_hp; }

    int get_default_hp() const { return get_hitpoints().default_hp; };

    virtual int get_damage() const = 0;

    virtual void damage(const Clock& clock, int damageAmount) = 0;

    virtual bool is_dead() const = 0;

protected:
    void default_render_health(Graphic& graphic_context, const Color& color, float frames_count) const;
};
