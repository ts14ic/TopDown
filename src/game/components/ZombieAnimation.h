#include <utility>

#pragma once

#include <game/timer/Timer.h>
#include <string>

class ZombieAnimation {
public:
    struct Animation {
        std::string name;
        int frames = 0;
        std::size_t speed = 0;
    };

    static const Animation MOVING;
    static const Animation ATTACKING;
    static const Animation DYING;

    void set_animation(Animation animation, const Clock& clock) {
        _current = std::move(animation);
        reset_frame();
        reset_timer(clock);
    }

    std::string get_tex_name() const {
        if (_current.frames == 0) {
            return _current.name;
        }
        return _current.name + std::to_string(_frame);
    }

    std::size_t get_animation_speed() const {
        return _current.speed;
    }

    int get_frames_count() const {
        return _current.frames;
    }

    int get_frame() const {
        return _frame;
    }

    bool is_last_frame() const {
        return _frame == _current.frames - 1;
    }

    void next_frame() {
        ++_frame;
    }

    void reset_frame() {
        _frame = 0;
    }

    bool ticks_passed_since_start(const Clock& clock, std::size_t ticks) const {
        return _timer.ticks_passed_since_start(clock, ticks);
    }

    void reset_timer(const Clock& clock) {
        _timer.restart(clock);
    }

private:
    int _frame = 0;
    Timer _timer;
    Animation _current = MOVING;
};

bool operator==(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);
bool operator!=(const ZombieAnimation::Animation& lhs, const ZombieAnimation::Animation& rhs);
