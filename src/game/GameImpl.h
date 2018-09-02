#pragma once

#include "Game.h"
#include "state/GameState.h"
#include "timer/Timer.h"
#include <engine/Engine.h>
#include <memory>

class GameImpl : public Game, public EventHandler {
public:
    explicit GameImpl(std::unique_ptr<Engine> engine);

    Engine& get_engine() override;

    void run_loop() override;

    void request_state_change(StateId stateId) override;

    void handle_window_event(const WindowEvent& event) override;

    void handle_key_event(const KeyboardEvent& event) override;

    void handle_mouse_event(const MouseScrollEvent& event) override;

    void handle_mouse_event(const MousePointEvent& event) override;

private:
    void change_state();

    void load_config();

    void load_resources();

    unsigned calculate_ms_per_frame(int frames_per_second) const;

    // todo add a loop input
    StateId _current_state_id = StateId::NONE;
    StateId _next_state_id = StateId::NONE;
    std::unique_ptr<GameState> _current_state;
    std::unique_ptr<Engine> _engine;
    unsigned _ms_per_frame;
};
