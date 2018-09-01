#pragma once

#include "Damageable.h"
#include "Weapon.h"
#include "game/timer/Timer.h"
#include "engine/input/Input.h"
#include <memory>
#include <bitset>

class Player : public virtual GameObject,
               public Damageable,
               public KeyboardEventHandler,
               public MouseEventHandler {
public:
    Player();

    Player(int x, int y);

    float get_x() const override;

    float get_y() const override;

    float get_angle() const override;

    float get_max_movement_speed() const override;

    float get_current_speed_x() const override;

    float get_current_speed_y() const override;

    void set_position(float x, float y) override;

    void set_x(float x) override;

    void set_y(float y) override;

    void set_angle(float a) override;

    void set_max_movement_speed(float movementSpeed) override;

    void set_current_speed_x(float speedX) override;

    void set_current_speed_y(float speedY) override;

    void set_current_speed(float speedX, float speedY) override;

    Circle get_circle() const override;

    std::string get_tex_name() const override;

    int get_hp() const override;

    int get_default_hp() const override;

    int get_damage() const override;

    bool is_dead() const override;

    void damage(const Clock &clock, int damageAmount) override;

    bool reloading() const;

    void handle_key_event(const KeyboardEvent &event) override;

    void handle_mouse_event(const MouseEvent &event) override;

    void handle_logic(Random& random, Engine& resources, Audio& audio);

    void handle_render(Engine &resources, Graphic &graphic, float predictionRatio);

    void addWeapon(Weapon weapon);

private:
    void select_next_weapon();

    void select_previous_weapon();

    void select_weapon(unsigned index);

    void update_speeds();

    float _x = 0;
    float _y = 0;
    float _current_speed_x = 0;
    float _current_speed_y = 0;
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
