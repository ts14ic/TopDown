#pragma once

#include "KeyboardKey.h"

class KeyboardEvent {
public:
    enum class Type {
        KEY_DOWN,
        KEY_UP,
    };

    KeyboardEvent(Type type, KeyboardKey_t key);

    Type get_type() const;

    KeyboardKey_t get_key() const;

    static bool is_key_down(KeyboardEvent event) { return event.get_type() == Type::KEY_DOWN; }

    static bool is_key_up(KeyboardEvent event) { return event.get_type() == Type::KEY_UP; }

private:
    Type _type;
    KeyboardKey_t _key;
};
