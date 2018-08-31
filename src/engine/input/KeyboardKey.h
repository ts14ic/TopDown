#pragma once

#include <cstdint>

using KeyboardKey_t = std::int32_t;

namespace detail {
    constexpr int apply_key_mask(KeyboardKey_t key, KeyboardKey_t level) {
        return static_cast<KeyboardKey_t>(key) | (1 << (level + 8));
    }
}

enum KeyboardKey : KeyboardKey_t {
    KEY_RETURN = detail::apply_key_mask('r', 0),
    KEY_ENTER = KEY_RETURN,
    KEY_ESCAPE = detail::apply_key_mask('e', 0),
    KEY_BACKSPACE = detail::apply_key_mask('b', 0),
    KEY_TAB = detail::apply_key_mask('t', 0),
    KEY_SPACE = detail::apply_key_mask('s', 0),
    KEY_CAPSLOCK = detail::apply_key_mask('c', 0),

    KEY_F1 = detail::apply_key_mask('1', 1),
    KEY_F2 = detail::apply_key_mask('2', 1),
    KEY_F3 = detail::apply_key_mask('3', 1),
    KEY_F4 = detail::apply_key_mask('4', 1),
    KEY_F5 = detail::apply_key_mask('5', 1),
    KEY_F6 = detail::apply_key_mask('6', 1),
    KEY_F7 = detail::apply_key_mask('7', 1),
    KEY_F8 = detail::apply_key_mask('8', 1),
    KEY_F9 = detail::apply_key_mask('9', 1),

    KEY_F10 = detail::apply_key_mask('0', 2),
    KEY_F11 = detail::apply_key_mask('1', 2),
    KEY_F12 = detail::apply_key_mask('2', 2),

    KEY_UP = detail::apply_key_mask('w', 3),
    KEY_DOWN = detail::apply_key_mask('s', 3),
    KEY_LEFT = detail::apply_key_mask('a', 3),
    KEY_RIGHT = detail::apply_key_mask('d', 3),
};
