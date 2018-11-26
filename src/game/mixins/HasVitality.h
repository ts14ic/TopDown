#pragma once

#include <game/components/Vitality.h>

class HasVitality {
public:
    virtual Vitality get_vitality() const = 0;

    virtual void set_vitality(Vitality vitality) = 0;

    int get_hp() const { return get_vitality().current_hp; }

    bool has_hp() const { return get_hp() > 0; }

    void set_hp(int hp) {
        Vitality vitality = get_vitality();
        vitality.current_hp = hp;
        set_vitality(vitality);
    }

    int get_default_hp() const { return get_vitality().default_hp; };

    void set_default_hp(int default_hp) {
        Vitality vitality = get_vitality();
        vitality.default_hp = default_hp;
        set_vitality(vitality);
    }
};
