//
// Created by ts14ic on 12/15/17.
//

#pragma once

#include "KeyboardKey.h"

class KeyboardEvent {
public:
    enum class Type {
        KeyDown,
        KeyUp,
    };

    KeyboardEvent();

    Type getType() const;

    KeyboardKey_t getKey() const;

    void setType(Type type);

    void setKey(KeyboardKey_t key);

private:
    Type mType;
    KeyboardKey_t mKey;
};
