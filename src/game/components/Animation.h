#include <utility>

#pragma once

#include <game/timer/Timer.h>
#include <string>
#include <vector>

namespace animation {
    class State {
    public:
        virtual ~State() = 0;

        virtual std::unique_ptr<State> clone() const = 0;

        virtual std::string get_tex_name() const = 0;

        virtual bool is_last_frame() const = 0;

        virtual bool is_frame_ended() const = 0;

        virtual bool is_animation_ended() const = 0;

        virtual void next_frame() = 0;

        virtual void forward_time() = 0;
    };

    class StaticState : public State {
    public:
        explicit StaticState(std::string name);

        ~StaticState() override;

        std::string get_tex_name() const override;

        bool is_last_frame() const override;

        bool is_frame_ended() const override;

        bool is_animation_ended() const override;

        void next_frame() override;

        void forward_time() override;

        std::unique_ptr<State> clone() const override;

    private:
        std::string _name;
    };

    class OneshotState : public State {
    public:
        OneshotState(std::string name, std::vector<std::size_t> frame_durations);

        ~OneshotState() override;

        std::string get_tex_name() const override;

        bool is_last_frame() const override;

        bool is_frame_ended() const override;

        bool is_animation_ended() const override;

        void next_frame() override;

        void forward_time() override;

        std::unique_ptr<State> clone() const override;

    public:
    private:
        std::string _name;
        std::size_t _frame;
        std::vector<std::size_t> _frame_durations;
        Timer _timer;
    };

    class RepeatableState : public State {
    public:
        RepeatableState(std::string name, std::vector<std::size_t> frame_durations);

        ~RepeatableState() override;

        std::string get_tex_name() const override;

        bool is_last_frame() const override;

        bool is_frame_ended() const override;

        bool is_animation_ended() const override;

        void next_frame() override;

        void forward_time() override;

        std::unique_ptr<State> clone() const override;

    public:
    private:
        std::string _name;
        std::size_t _frame;
        std::vector<std::size_t> _frame_durations;
        Timer _timer;
    };

    extern const StaticState ZOMBIE_MOVING;
    extern const RepeatableState ZOMBIE_ATTACKING;
    extern const OneshotState ZOMBIE_DYING;

    class Animation {
    public:
        void set_state(const animation::State& state) {
            _state = state.clone();
        }

        std::string get_tex_name() const {
            return _state->get_tex_name();
        }

        bool is_last_frame() const {
            return _state->is_last_frame();
        }

        bool is_frame_ended() const {
            return _state->is_frame_ended();
        }

        bool is_animation_ended() const {
            return _state->is_animation_ended();
        }

        void next_frame() {
            _state->next_frame();
        }

        void forward_time() {
            _state->forward_time();
        }

    private:
        std::unique_ptr<animation::State> _state;
    };
}
