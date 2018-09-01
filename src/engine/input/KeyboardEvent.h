#pragma once

#include "KeyboardKey.h"

class KeyboardEvent {
public:
    enum class Type {
        KeyDown,
        KeyUp,
    };

    KeyboardEvent(Type type, KeyboardKey_t key);

    Type get_type() const;

    KeyboardKey_t get_key() const;

private:
    Type _type;
    KeyboardKey_t _key;
};
