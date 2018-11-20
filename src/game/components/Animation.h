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

    struct State {
        std::string name;
        std::vector<std::size_t> frame_durations;
        AnimationType type = AnimationType::REPEATABLE;
        std::size_t frame = 0;
        Timer timer;
    };

    extern const State ZOMBIE_MOVING;
    extern const State ZOMBIE_ATTACKING;
    extern const State ZOMBIE_DYING;

    class Animation {
    public:
        void set_state(animation::State state) {
            _state = std::move(state);
            _state.frame = 0;
            _state.timer.restart();
        }

        std::string get_tex_name() const {
            if (_state.type == animation::AnimationType::STATIC) {
                return _state.name;
            }
            return _state.name + std::to_string(_state.frame);
        }

        bool is_last_frame() const {
            return _state.frame + 1 >= _state.frame_durations.size();
        }

        bool is_frame_ended() const {
            if (_state.type == animation::AnimationType::STATIC) {
                return true;
            }
            return _state.timer.ticks_passed_since_start(_state.frame_durations[_state.frame]);
        }

        bool is_animation_ended() const {
            return is_last_frame() && is_frame_ended();
        }

        void next_frame() {
            if (_state.type == animation::AnimationType::STATIC) {
                return;
            }
            if (is_last_frame()) {
                if (_state.type == animation::AnimationType::REPEATABLE) {
                    _state.frame = 0;
                }
            } else {
                ++_state.frame;
            }
        }

        void forward_time() {
            if (_state.type == animation::AnimationType::STATIC) {
                return;
            }
            if (is_frame_ended()) {
                next_frame();
                if (not (_state.type == animation::AnimationType::ONESHOT and is_last_frame())) {
                    _state.timer.restart();
                }
            }
        }

    private:
        animation::State _state = animation::ZOMBIE_MOVING;
    };
}

bool operator==(const animation::State& lhs, const animation::State& rhs);

bool operator!=(const animation::State& lhs, const animation::State& rhs);
