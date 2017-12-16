//
// Created by ts14ic on 12/15/17.
//

#pragma once

#include <cstdint>

using KeyboardKey_t = std::int32_t;

namespace detail {
    constexpr int applyKeyMask(KeyboardKey_t key, KeyboardKey_t level) {
        return static_cast<KeyboardKey_t>(key) | (1 << (level + 8));
    }
}

enum KeyboardKey : KeyboardKey_t {
    KEY_RETURN = detail::applyKeyMask('r', 0),
    KEY_ENTER = KEY_RETURN,
    KEY_ESCAPE = detail::applyKeyMask('e', 0),
    KEY_BACKSPACE = detail::applyKeyMask('b', 0),
    KEY_TAB = detail::applyKeyMask('t', 0),
    KEY_SPACE = detail::applyKeyMask('s', 0),
    KEY_CAPSLOCK = detail::applyKeyMask('c', 0),

    KEY_F1 = detail::applyKeyMask('1', 1),
    KEY_F2 = detail::applyKeyMask('2', 1),
    KEY_F3 = detail::applyKeyMask('3', 1),
    KEY_F4 = detail::applyKeyMask('4', 1),
    KEY_F5 = detail::applyKeyMask('5', 1),
    KEY_F6 = detail::applyKeyMask('6', 1),
    KEY_F7 = detail::applyKeyMask('7', 1),
    KEY_F8 = detail::applyKeyMask('8', 1),
    KEY_F9 = detail::applyKeyMask('9', 1),

    KEY_F10 = detail::applyKeyMask('0', 2),
    KEY_F11 = detail::applyKeyMask('1', 2),
    KEY_F12 = detail::applyKeyMask('2', 2),

    KEY_UP = detail::applyKeyMask('w', 3),
    KEY_DOWN = detail::applyKeyMask('s', 3),
    KEY_LEFT = detail::applyKeyMask('a', 3),
    KEY_RIGHT = detail::applyKeyMask('d', 3),
};
