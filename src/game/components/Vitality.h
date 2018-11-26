#pragma once

struct Vitality {
    Vitality() {
        current_hp = 0;
        default_hp = 0;
    }

    explicit Vitality(int default_hp): Vitality{default_hp, default_hp} {}

    Vitality(int current_hp, int default_hp) {
        this->current_hp = current_hp;
        this->default_hp = default_hp;
    }

    int current_hp;
    int default_hp;
};
