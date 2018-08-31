#pragma once

#include "GameState.h"
#include "game/object/Player.h"
#include "game/object/GameObject.h"
#include "engine/Engine.h"
#include "engine/Timer.h"

class StateMoon : public GameState {
public:
    explicit StateMoon(Engine& engine);

    StateMoon(const StateMoon& other);

    void handle_window_event(const WindowEvent &event) override;

    void handle_mouse_event(const MouseEvent &event) override;

    void handle_key_event(const KeyboardEvent &event) override;

    void handle_logic() override;

    void handle_render(float predictionRatio) override;

    void restrict_pos(GameObject&);

private:
    void parse_level_data();

private:
    Engine& _engine;

    std::string _background_tex;
    int const _level_width;
    int const _level_height;

    int _mouse_x;
    int _mouse_y;
    Player _player;
    Timer _enemy_spawn_cooldown;
};
