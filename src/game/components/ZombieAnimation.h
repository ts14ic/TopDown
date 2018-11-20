#include <utility>

#pragma once

#include <game/timer/Timer.h>
#include <string>

class ZombieAnimation {
public:
    enum AnimationType {
        STATIC,
        ONESHOT,
        REPEATABLE,
    };

    struct Animation {
        std::string name;
        int frames = 0;
        std::size_t speed = 0;
        AnimationType type = REPEATABLE;
    };

    static const Animation MOVING;
    static const Animation ATTACKING;
    static const Animation DYING;

    void set_animation(Animation animation, const Clock& clock) {
        _current_animation = std::move(animation);
        _frame = 0;
        _timer.restart(clock);
    }

    std::string get_tex_name() const {
        if (_current_animation.type == AnimationType::STATIC) {
            return _current_animation.name;
        }
        return _current_animation.name + std::to_string(_frame);
    }

    bool is_last_frame() const {
        return _frame + 1 >= _current_animation.frames;
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

    void forward_time(const Clock& clock) {
        if (_current_animation.type == AnimationType::STATIC) {
            return;
        }
        if (_timer.ticks_passed_since_start(clock, _current_animation.speed)) {
            next_frame();
            _timer.restart(clock);
        }
    }

private:
    int _frame = 0;
    Timer _timer;
    Animation _current_animation = MOVING;
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);

bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);
