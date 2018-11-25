#include <utility>

#pragma once

#include <game/timer/Timer.h>
#include <string>
#include <vector>

namespace animation {
    class Animation {
    public:
        virtual ~Animation() = 0;

        virtual std::unique_ptr<Animation> clone() const = 0;

        virtual std::string get_tex_name() const = 0;

        virtual bool is_last_frame() const = 0;

        virtual bool is_animation_ended() const = 0;

        virtual void update() = 0;
    };

    class StaticAnimation : public Animation {
    public:
        explicit StaticAnimation(std::string name);

        ~StaticAnimation() override;

        std::string get_tex_name() const override;

        bool is_last_frame() const override;

        bool is_animation_ended() const override;

        void update() override;

        std::unique_ptr<Animation> clone() const override;

    private:
        std::string _name;
    };

    class OneshotAnimation : public Animation {
    public:
        OneshotAnimation(std::string name, std::vector<std::size_t> frame_durations);

        ~OneshotAnimation() override;

        std::string get_tex_name() const override;

        bool is_last_frame() const override;

        bool is_animation_ended() const override;

        void update() override;

        std::unique_ptr<Animation> clone() const override;

    private:
        std::size_t get_frame() const;

        std::string _name;
        std::vector<std::size_t> _frame_durations;
        Timer _timer;
        std::size_t _time = 0;
        bool _started = 0;
    };

    class RepeatableAnimation : public Animation {
    public:
        RepeatableAnimation(std::string name, std::vector<std::size_t> frame_durations);

        ~RepeatableAnimation() override;

        std::string get_tex_name() const override;

        bool is_last_frame() const override;

        bool is_animation_ended() const override;

        void update() override;

        std::unique_ptr<Animation> clone() const override;

    private:
        bool is_frame_ended() const;

        void next_frame();

        std::string _name;
        std::size_t _frame;
        std::vector<std::size_t> _frame_durations;
        Timer _timer;
    };

    extern const StaticAnimation ZOMBIE_MOVING;
    extern const RepeatableAnimation ZOMBIE_ATTACKING;
    extern const OneshotAnimation ZOMBIE_DYING;

    extern const StaticAnimation PLAYER_HANDS;
    extern const StaticAnimation PLAYER_PISTOL;
    extern const StaticAnimation PLAYER_SHOTGUN;
    extern const StaticAnimation PLAYER_UZI;
    extern const StaticAnimation PLAYER_AURA;
}

class Sprite {
public:
    Sprite() = default;

    explicit Sprite(const animation::Animation& state)
            : _animation{state.clone()} {
    }

    void set_state(const animation::Animation& state) {
        _animation = state.clone();
    }

    std::string get_tex_name() const {
        return _animation->get_tex_name();
    }

    bool is_last_frame() const {
        return _animation->is_last_frame();
    }

    bool is_animation_ended() const {
        return _animation->is_animation_ended();
    }

    void update() {
        _animation->update();
    }

private:
    std::unique_ptr<animation::Animation> _animation;
};
