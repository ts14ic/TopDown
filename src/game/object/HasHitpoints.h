#pragma once

#include <game/components/Hitpoints.h>

class HasHitpoints {
public:
    virtual Hitpoints get_hitpoints() const = 0;

    int get_hp() const { return get_hitpoints().current_hp; }

    int get_default_hp() const { return get_hitpoints().default_hp; };
};
