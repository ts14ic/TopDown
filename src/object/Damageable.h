//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include "../texture/Texture.h"
#include "../engine/InputContext.h"
#include "../engine/RenderContext.h"
#include "GameObject.h"

class Damageable : public virtual GameObject {
public:
    virtual int hp() const = 0;

    virtual int defaultHp() const = 0;

    virtual int dmg() const = 0;

    virtual void damage(int v) = 0;

    virtual bool dead() const = 0;

protected:
    void default_render_health(RenderContext& engine, SDL_Color const& c) const;
};
