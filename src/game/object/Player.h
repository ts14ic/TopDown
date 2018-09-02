#pragma once

#include "Damageable.h"
#include "Weapon.h"
#include <game/components/Weapons.h>
#include <game/timer/Timer.h>
#include <engine/input/Input.h>
#include <engine/geometry/Point2.h>
#include <memory>
#include <bitset>

class Player : public virtual GameObject,
               public Damageable,
               public KeyboardEventHandler,
               public MouseEventHandler {
public:
    Player();

    explicit Player(Point2<float> position);

    Transform get_transform() const override { return _transform; }

    void set_transform(Transform transform) override { _transform = transform; }

    Speed get_speed() const override { return _speed; }

    void set_speed(Speed speed) override { _speed = speed; }

    Hitpoints get_hitpoints() const override { return _hitpoints; }

    void set_hitpoints(Hitpoints hitpoints) override { _hitpoints = hitpoints; }

    std::string get_tex_name() const override;

    int get_damage() const override;

    bool is_dead() const override;

    void take_damage(const Clock& clock, int damageAmount) override;

    bool reloading() const;

    void add_weapon(Weapon weapon);

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

    void handle_logic(Random& random, Engine& engine, Audio& audio);

    void handle_render(Engine& engine, Graphic& graphic, float frames_count);

private:
    void update_speeds();

    enum InputState {
        INPUT_UP_PRESSED,
        INPUT_DOWN_PRESSED,
        INPUT_LEFT_PRESSED,
        INPUT_RIGHT_PRESSED,
        INPUT_TRIGGER_PRESSED,
        INPUT_LENGTH
    };

    Transform _transform;
    Speed _speed;
    Weapons _weapons;
    Hitpoints _hitpoints;
    Timer _damage_cooldown;
    std::bitset<INPUT_LENGTH> _input_state;
};
