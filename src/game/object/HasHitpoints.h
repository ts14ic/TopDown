#pragma once

#include <game/components/Hitpoints.h>

class HasHitpoints {
public:
    virtual Hitpoints get_hitpoints() const = 0;

    virtual void set_hitpoints(Hitpoints hitpoints) = 0;

    int get_hp() const { return get_hitpoints().current_hp; }

    bool has_hp() const { return get_hp() > 0; }

    void set_hp(int hp) {
        Hitpoints hitpoints = get_hitpoints();
        hitpoints.current_hp = hp;
        set_hitpoints(hitpoints);
    }

    int get_default_hp() const { return get_hitpoints().default_hp; };

    void set_default_hp(int default_hp) {
        Hitpoints hitpoints = get_hitpoints();
        hitpoints.default_hp = default_hp;
        set_hitpoints(hitpoints);
    }
};
