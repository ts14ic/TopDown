#include "WeaponInventory.h"

void WeaponInventory::select_next() {
    auto last = _weapons.size() - 1;
    if (_selected_weapon_index < last) {
        _selected_weapon_index++;
    } else {
        _selected_weapon_index = static_cast<unsigned>(last);
    }
}

void WeaponInventory::select_previous() {
    auto first = 0u;
    if (_selected_weapon_index > first) {
        _selected_weapon_index--;
    }
}

void WeaponInventory::select_by_index(unsigned index) {
    auto last = _weapons.size() - 1;
    if (index <= last) {
        _selected_weapon_index = index;
    }
}

void WeaponInventory::try_reload_selected() {
    if (!empty()) {
        _weapons[_selected_weapon_index].try_reload();
    }
}

void WeaponInventory::fire_from_selected(Engine& engine, GameObject& shooter, std::vector<Bullet>& bullets) {
    if (!empty()) {
        get_selected_mut().pull_trigger(engine, shooter, bullets);
    }
}

bool WeaponInventory::any_selected() const {
    return !empty() && _selected_weapon_index < _weapons.size();
}

bool WeaponInventory::is_selected_reloading() const {
    return !empty() && _weapons[_selected_weapon_index].is_reloading();
}
