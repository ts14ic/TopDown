#include <memory>

#include "Sprite.h"

const animation::StaticAnimation animation::ZOMBIE_MOVING{
        "zombie"
};
const animation::RepeatableAnimation animation::ZOMBIE_ATTACKING{
        "zombie_attack",
        /*frame durations*/{150, 125, 100, 75, 50, 25}
};
const animation::OneshotAnimation animation::ZOMBIE_DYING{
        "zombie_death",
        /*frame durations*/{75, 100, 130, 160, 190, 210, 240, 300}
};

animation::Animation::~Animation() = default;


animation::StaticAnimation::~StaticAnimation() = default;

animation::StaticAnimation::StaticAnimation(std::string name)
        : _name{std::move(name)} {
}

std::unique_ptr<animation::Animation> animation::StaticAnimation::clone() const {
    return std::make_unique<StaticAnimation>(*this);
}

std::string animation::StaticAnimation::get_tex_name() const {
    return _name;
}

bool animation::StaticAnimation::is_last_frame() const {
    return true;
}

bool animation::StaticAnimation::is_frame_ended() const {
    return true;
}

bool animation::StaticAnimation::is_animation_ended() const {
    return true;
}

void animation::StaticAnimation::next_frame() {
}

void animation::StaticAnimation::forward_time() {
}


animation::OneshotAnimation::~OneshotAnimation() = default;

animation::OneshotAnimation::OneshotAnimation(std::string name, std::vector<std::size_t> frame_durations)
        : _name{std::move(name)}, _frame_durations{std::move(frame_durations)} {
}

std::unique_ptr<animation::Animation> animation::OneshotAnimation::clone() const {
    return std::make_unique<OneshotAnimation>(*this);
}

std::string animation::OneshotAnimation::get_tex_name() const {
    return _name + std::to_string(_frame);
}

bool animation::OneshotAnimation::is_last_frame() const {
    return _frame + 1 >= _frame_durations.size();
}

bool animation::OneshotAnimation::is_frame_ended() const {
    return _timer.ticks_passed_since_start(_frame_durations[_frame]);
}

bool animation::OneshotAnimation::is_animation_ended() const {
    return is_last_frame() && is_frame_ended();
}

void animation::OneshotAnimation::next_frame() {
    if (!is_last_frame()) {
        ++_frame;
    }
}

void animation::OneshotAnimation::forward_time() {
    if (is_frame_ended()) {
        next_frame();
        if (not is_last_frame()) {
            _timer.restart();
        }
    }
}


animation::RepeatableAnimation::~RepeatableAnimation() = default;

animation::RepeatableAnimation::RepeatableAnimation(std::string name, std::vector<std::size_t> frame_durations)
        : _name{std::move(name)}, _frame_durations{std::move(frame_durations)} {
}

std::unique_ptr<animation::Animation> animation::RepeatableAnimation::clone() const {
    return std::make_unique<RepeatableAnimation>(*this);
}

std::string animation::RepeatableAnimation::get_tex_name() const {
    return _name + std::to_string(_frame);
}

bool animation::RepeatableAnimation::is_last_frame() const {
    return _frame + 1 >= _frame_durations.size();
}

bool animation::RepeatableAnimation::is_frame_ended() const {
    return _timer.ticks_passed_since_start(_frame_durations[_frame]);
}

bool animation::RepeatableAnimation::is_animation_ended() const {
    return is_last_frame();
}

void animation::RepeatableAnimation::next_frame() {
    if (is_last_frame()) {
        _frame = 0;
    } else {
        ++_frame;
    }
}

void animation::RepeatableAnimation::forward_time() {
    if (is_frame_ended()) {
        next_frame();
        if (not is_last_frame()) {
            _timer.restart();
        }
    }
}
