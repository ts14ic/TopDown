#pragma once

#include "Transform.h"
#include <game/object/Weapon.h>
#include <vector>
#include <string>

class WeaponInventory {
public:
    void add(const Weapon& weapon) { _weapons.push_back(weapon); }

    bool empty() const { return _weapons.empty(); }

    bool any_selected() const;

    void select_next();

    void select_previous();

    void select_by_index(unsigned index);

    std::string get_selected_name() const { return get_selected().get_name(); }

    bool is_selected_reloading() const;

    void try_reload_selected();

    int fire_from_selected(Audio& audio);

    Weapon& get_selected_mut() { return _weapons[_selected_weapon_index]; }

    const Weapon& get_selected() const { return _weapons[_selected_weapon_index]; }

private:
    std::vector<Weapon> _weapons;
    unsigned _selected_weapon_index = 0;
};