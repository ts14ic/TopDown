#pragma once

#include "KeyboardKey.h"

class KeyboardEvent {
public:
    enum class Type {
        KeyDown,
        KeyUp,
    };

    KeyboardEvent();

    Type get_type() const;

    KeyboardKey_t get_key() const;

    void set_type(Type type);

    void set_key(KeyboardKey_t key);

private:
    Type _type;
    KeyboardKey_t _key;
};
