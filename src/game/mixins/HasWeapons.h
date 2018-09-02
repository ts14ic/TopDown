#pragma once

#include <game/components/Weapons.h>

class HasWeapons {
public:
    virtual Weapons get_weapons() const = 0;

    virtual void set_weapons(Weapons weapons) = 0;

    void add_weapon(const Weapon& weapon) {
        // TODO: Measure performance hits
        Weapons weapons = get_weapons();
        weapons.add(weapon);
        set_weapons(weapons);
    }

    bool is_reloading() const {
        return get_weapons().is_selected_reloading();
    }
};