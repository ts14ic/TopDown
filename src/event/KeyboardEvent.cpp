//
// Created by ts14ic on 12/15/17.
//

#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() = default;

KeyboardEvent::Type KeyboardEvent::getType() const {
    return mType;
}

int KeyboardEvent::getKey() const {
    return mKey;
}

void KeyboardEvent::setType(KeyboardEvent::Type type) {
    mType = type;
}

void KeyboardEvent::setKey(int key) {
    mKey = key;
}
