#pragma once

#include <bitset>
#include <engine/geometry/Point2.h>

class PlayerInput {
public:
    void move_mouse(Point2<int> position);

    bool mouse_moved() const { return _mouse_moved; }

    Point2<int> get_mouse_position() const { return _mouse_position; }

    Point2<int> pop_mouse_position();

    enum HoldAction : int {
        HOLD_NONE = -1,
        HOLD_UP = 0,
        HOLD_DOWN,
        HOLD_LEFT,
        HOLD_RIGHT,
        HOLD_TRIGGER,

        HOLD_ACTIONS_COUNT
    };

    void hold(HoldAction action);

    void release(HoldAction action);

    bool is_held(HoldAction action);

    enum QuickAction : int {
        QUICK_NONE = -1,
        QUICK_0 = 0,
        QUICK_1,
        QUICK_2,
        QUICK_3,
        QUICK_4,
        QUICK_5,
        QUICK_6,
        QUICK_7,
        QUICK_8,
        QUICK_9,
        QUICK_NEXT_WEAPON,
        QUICK_PREVIOUS_WEAPON,

        QUICK_ACTIONS_COUNT,
        QUICK_FIRST_ACTION = QUICK_0,
        QUICK_LAST_ACTION = QUICK_PREVIOUS_WEAPON,
    };

    void activate(QuickAction action);

    bool has_quick_actions() const;

    QuickAction pop_quick_action();

    static bool is_digit(QuickAction action);

    static unsigned to_digit(QuickAction action);

private:
    bool _mouse_moved = false;
    Point2<int> _mouse_position;
    std::bitset<HOLD_ACTIONS_COUNT> _hold_actions;
    std::bitset<QUICK_ACTIONS_COUNT> _quick_actions;
};
