#pragma once

#include "Damageable.h"
#include "Weapon.h"
#include "game/timer/Timer.h"
#include "engine/input/Input.h"
#include "game/utils/Point2.h"
#include <memory>
#include <bitset>

class Player : public virtual GameObject,
               public Damageable,
               public KeyboardEventHandler,
               public MouseEventHandler {
public:
    Player();

    Player(int x, int y);

    Point2<float> get_position() const override { return _position; }

    Point2<float>& get_position() override { return _position; }

    float get_angle() const override;

    void set_angle(float a) override;

    float get_max_movement_speed() const override;

    void set_max_movement_speed(float movementSpeed) override;

    float get_current_x_speed() const override;

    void set_current_x_speed(float x_speed) override;

    float get_current_y_speed() const override;

    void set_current_y_speed(float y_speed) override;

    void set_current_speed(float x_speed, float y_speed) override;

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
    float _current_x_speed = 0;
    float _current_y_speed = 0;
    float _max_movement_speed = 0;
    float _angle = 0.0f;

    std::vector<Weapon> _weapons;
    unsigned _selected_weapon_index = 0;
    int _hp = 0;

    Timer _damage_cooldown;

    enum InputState {
        UP_PRESSED,
        DOWN_PRESSED,
        LEFT_PRESSED,
        RIGHT_PRESSED,
        TRIGGER_PRESSED,
        LENGTH
    };
    std::bitset<LENGTH> _input_state;
};
