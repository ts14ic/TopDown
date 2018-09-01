#pragma once

#include "Damageable.h"
#include "Weapon.h"
#include "game/timer/Timer.h"
#include "engine/input/Input.h"
#include "engine/geometry/Point2.h"
#include <memory>
#include <bitset>

class Player : public virtual GameObject,
               public Damageable,
               public KeyboardEventHandler,
               public MouseEventHandler {
public:
    Player();

    explicit Player(Point2<float> position);

    Point2<float> get_position() const override { return _position; }

    using GameObject::set_position;

    void set_position(Point2<float> position) override { _position = position; }

    float get_angle() const override;

    void set_angle(float a) override;

    float get_max_movement_speed() const override;

    void set_max_movement_speed(float movementSpeed) override;

    Speed2<float> get_current_speed() const override { return _current_speed; }

    using GameObject::set_current_speed;

    void set_current_speed(Speed2<float> current_speed) override { _current_speed = current_speed; }

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    int get_hp() const override;

    int get_default_hp() const override;

    int get_damage() const override;

    bool is_dead() const override;

    void damage(const Clock& clock, int damageAmount) override;

    bool reloading() const;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

    void handle_logic(Random& random, Engine& engine, Audio& audio);

    void handle_render(Engine& engine, Graphic& graphic, float frames_count);

    void addWeapon(Weapon weapon);

private:
    void select_next_weapon();

    void select_previous_weapon();

    void select_weapon(unsigned index);

    void update_speeds();

    Point2<float> _position;
    Speed2<float> _current_speed;
    float _max_movement_speed = 0;
    float _angle = 0.0f;

    std::vector<Weapon> _weapons;
    unsigned _selected_weapon_index = 0;
    int _hp = 0;

    Timer _damage_cooldown;

    enum InputState {
        INPUT_UP_PRESSED,
        INPUT_DOWN_PRESSED,
        INPUT_LEFT_PRESSED,
        INPUT_RIGHT_PRESSED,
        INPUT_TRIGGER_PRESSED,
        INPUT_LENGTH
    };
    std::bitset<INPUT_LENGTH> _input_state;
};
