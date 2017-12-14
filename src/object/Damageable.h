//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "GameObject.h"

class Color;

class Clock;

class Damageable : public virtual GameObject {
public:
    virtual int hp() const = 0;

    virtual int defaultHp() const = 0;

    virtual int dmg() const = 0;

    virtual void damage(const Clock& clock, int damageAmount) = 0;

    virtual bool dead() const = 0;

protected:
    void default_render_health(GraphicContext& graphicContext, Color const& color) const;
};
