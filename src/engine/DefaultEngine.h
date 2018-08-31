#pragma once

#include "Engine.h"
#include "game/state/GameState.h"
#include "engine/ContextInjector.h"
#include "engine/resources/Resources.h"
#include "Timer.h"
#include "Clock.h"
#include "graphic/GraphicContext.h"
#include "AudioContext.h"
#include "Random.h"
#include <memory>

class DefaultEngine : public Engine,
                      public EventHandler {
public:
    DefaultEngine(
            int screen_width, int screen_height,
            ContextInjector* context_injector
    );

    void run_loop() override;

    void request_state_change(StateId stateId) override;

    GraphicContext& get_graphic_context() override;

    AudioContext& get_audio_context() override;

    Resources& get_resources() override;

    Random& get_random() override;

    const Clock& get_clock() override;

    void handle_window_event(const WindowEvent &event) override;

    void handle_key_event(const KeyboardEvent &event) override;

    void handle_mouse_event(const MouseEvent &event) override;

    void set_input_context(std::unique_ptr<InputContext> inputContext) override;

    void set_graphic_context(std::unique_ptr<GraphicContext> graphicContext) override;

    void set_audio_context(std::unique_ptr<AudioContext> audioContext) override;

    void set_resources(std::unique_ptr<Resources> resources) override;

    void set_random(std::unique_ptr<Random> random) override;

private:
    void change_state();

    void load_resources();

private:
    // todo add a loop input
    StateId _current_state_id = StateId::null;
    StateId _next_state_id = StateId::null;
    std::unique_ptr<GameState> _current_state;

    std::unique_ptr<Resources> _resources;
    std::unique_ptr<GraphicContext> _graphic_context;
    std::unique_ptr<AudioContext> _audio_context;
    std::unique_ptr<InputContext> _input_context;
    std::unique_ptr<Random> _random;
};
