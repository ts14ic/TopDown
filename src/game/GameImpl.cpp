#include "GameImpl.h"
#include "state/StateIntro.h"
#include "state/StateMoon.h"
#include <io/files/files.h>
#include <io/json/json.h>

constexpr unsigned MS_ONE_SECOND = 1000;
constexpr unsigned DEFAULT_FRAMES_PER_SECOND = 30;

GameImpl::GameImpl(
        std::unique_ptr<Engine> engine
) : _engine{std::move(engine)} {
    _ms_per_frame = calculate_ms_per_frame(DEFAULT_FRAMES_PER_SECOND);

    load_config();
    load_resources();
}

unsigned GameImpl::calculate_ms_per_frame(int frames_per_second) const {
    return MS_ONE_SECOND / frames_per_second;
}

void GameImpl::run_loop() {
    _current_state = std::make_unique<StateIntro>(*this);
    _engine->get_input().set_event_handler(*this);

    const auto& clock = _engine->get_clock();
    auto previous_time = clock.get_current_time();
    auto lag_time = 0UL;

    while (_current_state_id != StateId::exit) {
        auto new_time = clock.get_current_time();
        lag_time += new_time - previous_time;
        previous_time = new_time;

        _engine->get_input().poll_events();

        while (lag_time >= _ms_per_frame) {
            _current_state->handle_logic();
            lag_time -= _ms_per_frame;
        }

        change_state();

        _current_state->handle_render(static_cast<float>(lag_time) / _ms_per_frame);
    }
}

void GameImpl::change_state() {
    if (_next_state_id != StateId::null) {
        if (_next_state_id != StateId::exit) {
            _current_state = nullptr;
        }

        switch (_next_state_id) {
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

void GameImpl::request_state_change(StateId stateId) {
    if (_next_state_id != StateId::exit) {
        _next_state_id = stateId;
    }
}

Engine& GameImpl::get_engine() {
    return *_engine;
}

void GameImpl::handle_window_event(const WindowEvent& event) {
    switch (event.get_type()) {
        case WindowEvent::Type::Close: {
            request_state_change(StateId::exit);
            break;
        }
    }
}

void GameImpl::handle_key_event(const KeyboardEvent& event) {
    _current_state->handle_key_event(event);
}

void GameImpl::handle_mouse_event(const MouseScrollEvent& event) {
    _current_state->handle_mouse_event(event);
}

void GameImpl::handle_mouse_event(const MousePointEvent& event) {
    _current_state->handle_mouse_event(event);
}

void GameImpl::load_config() {
    auto document = json::parse_json(files::read_file_to_string("data/config.json"));

    _ms_per_frame = calculate_ms_per_frame(json::get_uint(document, "/fps"));
}

void GameImpl::load_resources() {
    auto document = json::parse_json(files::read_file_to_string("data/common_media.json"));

    using json::get_object;
    using json::get_czstring;

    for (const auto& entry : get_object(document, "/textures")) {
        _engine->get_graphic().load_texture(get_czstring(entry.name), get_czstring(entry.value));
    }

    for (const auto& entry : get_object(document, "/sounds")) {
        _engine->get_audio().load_sound(get_czstring(entry.name), get_czstring(entry.value));
    }

    for (const auto& entry : get_object(document, "/music")) {
        _engine->get_audio().load_music(get_czstring(entry.name), get_czstring(entry.value));
    }
}
