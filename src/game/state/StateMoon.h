#pragma once

#include "GameState.h"
#include <game/object/Player.h>
#include <game/object/GameObject.h>
#include <game/Game.h>
#include <game/timer/Timer.h>
#include <engine/geometry/Point2.h>

class StateMoon : public GameState {
public:
    explicit StateMoon(Game& game);

    StateMoon(const StateMoon& other);

    void handle_window_event(const WindowEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_logic() override;

    void handle_render(float frames_count) override;

    void restrict_pos(GameObject&);

private:
    void parse_level_data();

    Point2<int> make_random_point() const;

    bool position_out_of_level_area(Point2<float> position) const;

    void render_crosshair(float frames_count);

private:
    Game& _game;
    std::string _background_tex;
    const int _level_width;
    const int _level_height;
    Point2<int> _mouse_pos;

    Player _player;
    float _crosshair_angle;

    Timer _enemy_spawn_cooldown;
};
