#include "Weapons.h"

void Weapons::select_next() {
    auto last = _weapons.size() - 1;
    if (_selected_weapon_index < last) {
        _selected_weapon_index++;
    } else {
        _selected_weapon_index = static_cast<unsigned>(last);
    }
}

void Weapons::select_previous() {
    auto first = 0u;
    if (_selected_weapon_index > first) {
        _selected_weapon_index--;
    }
}

void Weapons::select_by_index(unsigned index) {
    auto last = _weapons.size() - 1;
    if (index <= last) {
        _selected_weapon_index = index;
    }
}

void Weapons::try_reload_selected(const Clock& clock) {
    if (!empty()) {
        _weapons[_selected_weapon_index].try_reload(clock);
    }
}

void Weapons::fire_from_selected(Engine& engine, GameObject& shooter) {
    if (!empty()) {
        get_selected_mut().pull_trigger(engine.get_random(), engine, engine.get_audio(), shooter);
    }
}

bool Weapons::any_selected() const {
    return !empty() && _selected_weapon_index < _weapons.size();
}

bool Weapons::is_selected_reloading() const {
    return !empty() && _weapons[_selected_weapon_index].is_reloading();
}
