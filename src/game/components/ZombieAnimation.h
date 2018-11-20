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
        AnimationType animation_type = REPEATABLE;
    };

    static const Animation MOVING;
    static const Animation ATTACKING;
    static const Animation DYING;

    void set_animation(Animation animation, const Clock& clock) {
        _current = std::move(animation);
        _frame = 0;
        _timer.restart(clock);
    }

    std::string get_tex_name() const {
        if (_current.animation_type == AnimationType::STATIC) {
            return _current.name;
        }
        return _current.name + std::to_string(_frame);
    }

    bool is_last_frame() const {
        return _frame + 1 == _current.frames;
    }

    void next_frame() {
        if (_current.animation_type == AnimationType::STATIC) {
            return;
        }
        if (!is_last_frame()) {
            ++_frame;

        } // Else we are on last frame. If it's a repeatable animation...
        else if (_current.animation_type == REPEATABLE) {
            // ... reset the frame
            _frame = 0;
        }
    }

    void tick(const Clock& clock) {
        if (_current.animation_type == AnimationType::STATIC) {
            return;
        }
        if (_timer.ticks_passed_since_start(clock, _current.speed)) {
            next_frame();
            _timer.restart(clock);
        }
    }

private:
    int _frame = 0;
    Timer _timer;
    Animation _current = MOVING;
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);

bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);
