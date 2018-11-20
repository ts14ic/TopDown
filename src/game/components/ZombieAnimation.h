#include <utility>

#pragma once

#include <game/timer/Timer.h>
#include <string>
#include <vector>

class ZombieAnimation {
public:
    enum AnimationType {
        STATIC,
        ONESHOT,
        REPEATABLE,
    };

    struct Animation {
        std::string name;
        std::vector<std::size_t> frame_speeds;
        AnimationType type = REPEATABLE;
    };

    static const Animation MOVING;
    static const Animation ATTACKING;
    static const Animation DYING;

    void set_animation(Animation animation) {
        _current_animation = std::move(animation);
        _frame = 0;
        _timer.restart();
    }

    std::string get_tex_name() const {
        if (_current_animation.type == AnimationType::STATIC) {
            return _current_animation.name;
        }
        return _current_animation.name + std::to_string(_frame);
    }

    bool is_last_frame() const {
        return _frame + 1 >= _current_animation.frame_speeds.size();
    }

    void next_frame() {
        if (_current_animation.type == AnimationType::STATIC) {
            return;
        }
        if (is_last_frame()) {
            if (_current_animation.type == REPEATABLE) {
                _frame = 0;
            }
        } else {
            ++_frame;
        }
    }

    void forward_time() {
        if (_current_animation.type == AnimationType::STATIC) {
            return;
        }
        if (_timer.ticks_passed_since_start(_current_animation.frame_speeds[_frame])) {
            next_frame();
            _timer.restart();
        }
    }

private:
    std::size_t _frame = 0;
    Timer _timer;
    Animation _current_animation = MOVING;
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);

bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);
