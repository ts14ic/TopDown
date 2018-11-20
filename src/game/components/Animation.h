#include <utility>

#pragma once

#include <game/timer/Timer.h>
#include <string>
#include <vector>

namespace animation {
    enum class AnimationType {
        STATIC,
        ONESHOT,
        REPEATABLE,
    };

    struct Preset {
        std::string name;
        std::vector<std::size_t> frame_durations;
        AnimationType type = AnimationType::REPEATABLE;
    };

    extern const Preset ZOMBIE_MOVING;
    extern const Preset ZOMBIE_ATTACKING;
    extern const Preset ZOMBIE_DYING;
}

class Animation {
public:
    void set_preset(animation::Preset preset) {
        _current_preset = std::move(preset);
        _frame = 0;
        _timer.restart();
    }

    std::string get_tex_name() const {
        if (_current_preset.type == animation::AnimationType::STATIC) {
            return _current_preset.name;
        }
        return _current_preset.name + std::to_string(_frame);
    }

    bool is_last_frame() const {
        return _frame + 1 >= _current_preset.frame_durations.size();
    }

    bool is_animation_ended() const {
        bool is_last_frame = this->is_last_frame();
        bool frame_ended;
        if (_current_preset.type != animation::AnimationType::STATIC) {
            frame_ended = _timer.ticks_passed_since_start(_current_preset.frame_durations[_frame]);
        } else {
            frame_ended = true;
        }
        return is_last_frame && frame_ended;
    }

    void next_frame() {
        if (_current_preset.type == animation::AnimationType::STATIC) {
            return;
        }
        if (is_last_frame()) {
            if (_current_preset.type == animation::AnimationType::REPEATABLE) {
                _frame = 0;
            }
        } else {
            ++_frame;
        }
    }

    void forward_time() {
        if (_current_preset.type == animation::AnimationType::STATIC) {
            return;
        }
        if (_timer.ticks_passed_since_start(_current_preset.frame_durations[_frame])) {
            next_frame();
            if (not (_current_preset.type == animation::AnimationType::ONESHOT and is_last_frame())) {
                _timer.restart();
            }
        }
    }

private:
    std::size_t _frame = 0;
    Timer _timer;
    animation::Preset _current_preset = animation::ZOMBIE_MOVING;
};

bool operator==(const animation::Preset& lhs, const animation::Preset& rhs);

bool operator!=(const animation::Preset& lhs, const animation::Preset& rhs);
