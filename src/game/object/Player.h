#pragma once

#include "Damageable.h"
#include "Weapon.h"
#include "Bullet.h"
#include <game/mixins/HasPlayerInput.h>
#include <game/mixins/HasWeaponInventory.h>
#include <game/timer/Timer.h>
#include <memory>
#include <bitset>

class Player : public virtual GameObject,
               public Damageable,
               public HasPlayerInput,
               public HasWeaponInventory {
public:
    Player();

    explicit Player(Point2d<float> position);

    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

    Speed get_speed() const override { return _speed; }

    void set_speed(Speed speed) override { _speed = speed; }

    Hitpoints get_hitpoints() const override { return _hitpoints; }

    void set_hitpoints(Hitpoints hitpoints) override { _hitpoints = hitpoints; }

    std::string get_tex_name() const override;

    WeaponInventory get_inventory() const override { return _inventory; }

    void set_weapons(WeaponInventory inventory) override { _inventory = inventory; }

    PlayerInput get_player_input() const override { return _input; }

    void set_player_input(PlayerInput input) override { _input = input; }

    bool is_dead() const override;

    void take_damage(int damage_amount) override;

    void handle_logic(Engine& engine, std::vector<Bullet>& bullets);

    void handle_render(Graphic& graphic, float frames_count);

private:
    void update_speeds();

    void handle_weapon_selection();

    Transform _transform;
    Speed _speed;
    WeaponInventory _inventory;
    PlayerInput _input;
    Hitpoints _hitpoints;
    Timer _damage_cooldown;
};
