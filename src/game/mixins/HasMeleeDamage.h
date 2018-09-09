#pragma once

class HasMeleeDamage {
public:
    virtual ~HasMeleeDamage() = default;

    virtual int get_melee_damage() const = 0;
};