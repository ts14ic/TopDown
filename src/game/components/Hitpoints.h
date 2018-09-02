#pragma once

struct Hitpoints {
    Hitpoints() {
        current_hp = 0;
        default_hp = 0;
    }

    explicit Hitpoints(int default_hp): Hitpoints{default_hp, default_hp} {}

    Hitpoints(int current_hp, int default_hp) {
        this->current_hp = current_hp;
        this->default_hp = default_hp;
    }

    int current_hp;
    int default_hp;
};
