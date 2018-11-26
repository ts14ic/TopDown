#pragma once

#include <game/components/WeaponInventory.h>

class HasWeaponInventory {
public:
    virtual WeaponInventory get_inventory() const = 0;

    virtual void set_weapons(WeaponInventory inventory) = 0;

    void add_weapon(const Weapon& weapon) {
        // TODO: Measure performance hits
        WeaponInventory inventory = get_inventory();
        inventory.add(weapon);
        set_weapons(inventory);
    }

    bool is_reloading() const {
        return get_inventory().is_selected_reloading();
    }
};