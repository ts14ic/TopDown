#pragma once

#include "Game.h"
#include "game/state/GameState.h"
#include "game/timer/Timer.h"
#include "engine/Engine.h"
#include "engine/clock/Clock.h"
#include "engine/graphic/GraphicContext.h"
#include "engine/audio/AudioContext.h"
#include "engine/random/Random.h"
#include <memory>
#include <engine/Engine.h>

class GameImpl : public Game, public EventHandler {
public:
    GameImpl(
            std::unique_ptr<Engine> resources,
            std::unique_ptr<Random> random,
            std::unique_ptr<GraphicContext> graphic_context,
            std::unique_ptr<AudioContext> audio_context,
            std::unique_ptr<InputContext> input_context
    );

    void run_loop() override;

    void request_state_change(StateId stateId) override;

    GraphicContext& get_graphic_context() override;

    AudioContext& get_audio_context() override;

    Engine& get_engine() override;

    Random& get_random() override;

    const Clock& get_clock() override;

    void handle_window_event(const WindowEvent &event) override;

    void handle_key_event(const KeyboardEvent &event) override;

    void handle_mouse_event(const MouseEvent &event) override;

private:
    void change_state();

    void load_resources();

private:
    // todo add a loop input
    StateId _current_state_id = StateId::null;
    StateId _next_state_id = StateId::null;
    std::unique_ptr<GameState> _current_state;

    std::unique_ptr<Engine> _resources;
    std::unique_ptr<GraphicContext> _graphic_context;
    std::unique_ptr<AudioContext> _audio_context;
    std::unique_ptr<InputContext> _input_context;
    std::unique_ptr<Random> _random;
};
