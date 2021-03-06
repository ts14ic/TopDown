#pragma once

#include "GameState.h"
#include <game/object/Player.h>
#include <game/object/Zombie.h>
#include <game/object/Werewolf.h>
#include <game/Game.h>
#include <game/timer/Timer.h>
#include <engine/geometry/Point2d.h>

class StateMoon : public GameState {
public:
    explicit StateMoon(Game& game);

    void handle_window_event(const WindowEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_logic() override;

    void handle_render(float milliseconds_passed, float milliseconds_per_frame) override;

private:
    Engine& get_engine() const {
        return _game.get_engine();
    }

    void handle_player_logic();

    void handle_bullet_logic();

    void handle_zombie_logic();

    void handle_werewolf_logic();

    void restrict_pos(GameObject&);

    void parse_level_data();

    Point2d<int> make_random_point() const;

    bool position_out_of_level_area(Point2d<float> position) const;

    void render_crosshair(float frames_count);

private:
    Game& _game;
    std::string _background_tex;
    const int _level_width;
    const int _level_height;

    Player _player;
    std::vector<Bullet> _bullets;
    std::vector<Zombie> _zombies;
    std::vector<Werewolf> _werewolves;
    float _crosshair_angle = 0;

    Timer _enemy_spawn_cooldown;
};
