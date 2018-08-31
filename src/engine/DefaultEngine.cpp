#include "DefaultEngine.h"
#include "game/state/StateIntro.h"
#include "game/state/StateMoon.h"

constexpr unsigned MS_ONE_SECOND = 1000;
constexpr unsigned FRAMES_PER_SECOND = 60;
constexpr unsigned MS_PER_FRAME = MS_ONE_SECOND / FRAMES_PER_SECOND;

DefaultEngine::DefaultEngine(
        int screen_width,
        int screen_height,
        ContextInjector* context_injector) {
    context_injector->inject(*this, screen_width, screen_height);

    load_resources();
}

void DefaultEngine::run_loop() {
    _current_state = std::make_unique<StateIntro>(*this);

    const auto& clock = get_clock();
    auto previous_time = clock.get_current_time();
    auto lag_time = 0UL;

    while(_current_state_id != StateId::exit) {
        auto new_time = clock.get_current_time();
        lag_time += new_time - previous_time;
        previous_time = new_time;

        _input_context->poll_events(*this);

        while(lag_time >= MS_PER_FRAME) {
            _current_state->handle_logic();
            lag_time -= MS_PER_FRAME;
        }

        change_state();

        _current_state->handle_render(static_cast<float>(lag_time) / MS_PER_FRAME);
    }
}

void DefaultEngine::change_state() {
    if(_next_state_id != StateId::null) {
        if(_next_state_id != StateId::exit) {
            _current_state.reset(nullptr);
        }

        switch(_next_state_id) {
            case StateId::intro:
                _current_state = std::make_unique<StateIntro>(*this);
                break;

            case StateId::moon:
                _current_state = std::make_unique<StateMoon>(*this);
                break;

            default:;
        }

        _current_state_id = _next_state_id;
        _next_state_id = StateId::null;
    }
}

void DefaultEngine::request_state_change(StateId stateId) {
    if(_next_state_id != StateId::exit) {
        _next_state_id = stateId;
    }
}

GraphicContext& DefaultEngine::get_graphic_context() {
    return *_graphic_context;
}

AudioContext& DefaultEngine::get_audio_context() {
    return *_audio_context;
}

Resources& DefaultEngine::get_resources() {
    return *_resources;
}

Random& DefaultEngine::get_random() {
    return *_random;
}

const Clock& DefaultEngine::get_clock() {
    return _resources->get_clock();
}

void DefaultEngine::set_input_context(std::unique_ptr<InputContext> inputContext) {
    _input_context = std::move(inputContext);
}

void DefaultEngine::set_graphic_context(std::unique_ptr<GraphicContext> graphicContext) {
    _graphic_context = std::move(graphicContext);
}

void DefaultEngine::set_audio_context(std::unique_ptr<AudioContext> audioContext) {
    _audio_context = std::move(audioContext);
}

void DefaultEngine::set_resources(std::unique_ptr<Resources> resources) {
    _resources = std::move(resources);
}

void DefaultEngine::set_random(std::unique_ptr<Random> random) {
    _random = std::move(random);
}

void DefaultEngine::handle_window_event(const WindowEvent &event) {
    switch(event.get_type()) {
        case WindowEvent::Type::Close: {
            request_state_change(StateId::exit);
            break;
        }

//        default: {
//            _current_state->handle_window_event(input);
//            break;
//        }
    }
}

void DefaultEngine::handle_key_event(const KeyboardEvent &event) {
    _current_state->handle_key_event(event);
}

void DefaultEngine::handle_mouse_event(const MouseEvent &event) {
    _current_state->handle_mouse_event(event);
}
