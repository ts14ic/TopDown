#include <memory>

#include "Animation.h"

const animation::StaticState animation::ZOMBIE_MOVING{
        "zombie"
};
const animation::RepeatableState animation::ZOMBIE_ATTACKING{
        "zombie_attack",
        /*frame durations*/{150, 125, 100, 75, 50, 25}
};
const animation::OneshotState animation::ZOMBIE_DYING{
        "zombie_death",
        /*frame durations*/{75, 100, 130, 160, 190, 210, 240, 300}
};

animation::State::~State() = default;


animation::StaticState::~StaticState() = default;

animation::StaticState::StaticState(std::string name)
        : _name{std::move(name)} {
}

std::unique_ptr<animation::State> animation::StaticState::clone() const {
    return std::make_unique<StaticState>(*this);
}

std::string animation::StaticState::get_tex_name() const {
    return _name;
}

bool animation::StaticState::is_last_frame() const {
    return true;
}

bool animation::StaticState::is_frame_ended() const {
    return true;
}

bool animation::StaticState::is_animation_ended() const {
    return true;
}

void animation::StaticState::next_frame() {
}

void animation::StaticState::forward_time() {
}


animation::OneshotState::~OneshotState() = default;

animation::OneshotState::OneshotState(std::string name, std::vector<std::size_t> frame_durations)
        : _name{std::move(name)}, _frame_durations{std::move(frame_durations)} {
}

std::unique_ptr<animation::State> animation::OneshotState::clone() const {
    return std::make_unique<OneshotState>(*this);
}

std::string animation::OneshotState::get_tex_name() const {
    return _name + std::to_string(_frame);
}

bool animation::OneshotState::is_last_frame() const {
    return _frame + 1 >= _frame_durations.size();
}

bool animation::OneshotState::is_frame_ended() const {
    return _timer.ticks_passed_since_start(_frame_durations[_frame]);
}

bool animation::OneshotState::is_animation_ended() const {
    return is_last_frame() && is_frame_ended();
}

void animation::OneshotState::next_frame() {
    if (!is_last_frame()) {
        ++_frame;
    }
}

void animation::OneshotState::forward_time() {
    if (is_frame_ended()) {
        next_frame();
        if (not is_last_frame()) {
            _timer.restart();
        }
    }
}


animation::RepeatableState::~RepeatableState() = default;

animation::RepeatableState::RepeatableState(std::string name, std::vector<std::size_t> frame_durations)
        : _name{std::move(name)}, _frame_durations{std::move(frame_durations)} {
}

std::unique_ptr<animation::State> animation::RepeatableState::clone() const {
    return std::make_unique<RepeatableState>(*this);
}

std::string animation::RepeatableState::get_tex_name() const {
    return _name + std::to_string(_frame);
}

bool animation::RepeatableState::is_last_frame() const {
    return _frame + 1 >= _frame_durations.size();
}

bool animation::RepeatableState::is_frame_ended() const {
    return _timer.ticks_passed_since_start(_frame_durations[_frame]);
}

bool animation::RepeatableState::is_animation_ended() const {
    return is_last_frame();
}

void animation::RepeatableState::next_frame() {
    if (is_last_frame()) {
        _frame = 0;
    } else {
        ++_frame;
    }
}

void animation::RepeatableState::forward_time() {
    if (is_frame_ended()) {
        next_frame();
        if (not is_last_frame()) {
            _timer.restart();
        }
    }
}
