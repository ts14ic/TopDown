#include "GameImpl.h"
#include "game/state/StateIntro.h"
#include "game/state/StateMoon.h"
#include "io/files/files.h"
#include "io/json/get_value.h"
#include "io/json/parse_json.h"

constexpr unsigned MS_ONE_SECOND = 1000;
constexpr unsigned FRAMES_PER_SECOND = 60;
constexpr unsigned MS_PER_FRAME = MS_ONE_SECOND / FRAMES_PER_SECOND;

GameImpl::GameImpl(
        std::unique_ptr<Engine> engine
) : _engine{std::move(engine)} {

    load_resources();
}

void GameImpl::run_loop() {
    _current_state = std::make_unique<StateIntro>(*this);

    const auto& clock = _engine->get_clock();
    auto previous_time = clock.get_current_time();
    auto lag_time = 0UL;

    while(_current_state_id != StateId::exit) {
        auto new_time = clock.get_current_time();
        lag_time += new_time - previous_time;
        previous_time = new_time;

        _engine->get_input().poll_events(*this);

        while(lag_time >= MS_PER_FRAME) {
            _current_state->handle_logic();
            lag_time -= MS_PER_FRAME;
        }

        change_state();

        _current_state->handle_render(static_cast<float>(lag_time) / MS_PER_FRAME);
    }
}

void GameImpl::change_state() {
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

void GameImpl::request_state_change(StateId stateId) {
    if(_next_state_id != StateId::exit) {
        _next_state_id = stateId;
    }
}

Engine& GameImpl::get_engine() {
    return *_engine;
}

void GameImpl::handle_window_event(const WindowEvent &event) {
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

void GameImpl::handle_key_event(const KeyboardEvent &event) {
    _current_state->handle_key_event(event);
}

void GameImpl::handle_mouse_event(const MouseEvent &event) {
    _current_state->handle_mouse_event(event);
}

void GameImpl::load_resources() {
    auto doc = json::parse_json(files::read_file_to_string("data/common_media.json"));

    using json::get_value;
    auto texturesMap = get_value<rapidjson::Value::ConstObject>(doc, "/textures");
    for (const auto& entry : texturesMap) {
        _engine->get_graphic().load_texture(get_value<const char*>(entry.name, ""), get_value<const char*>(entry.value, ""));
    }

    auto soundsMap = get_value<rapidjson::Value::ConstObject>(doc, "/sounds");
    for (const auto& entry : soundsMap) {
        _engine->get_audio().load_sound(get_value<const char*>(entry.name, ""), get_value<const char*>(entry.value, ""));
    }

    auto musicMap = get_value<rapidjson::Value::ConstObject>(doc, "/music");
    for (const auto& entry : musicMap) {
        _engine->get_audio().load_music(get_value<const char*>(entry.name, ""), get_value<const char*>(entry.value, ""));
    }
}
