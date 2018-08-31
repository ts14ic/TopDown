#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() = default;

KeyboardEvent::Type KeyboardEvent::get_type() const {
    return _type;
}

KeyboardKey_t KeyboardEvent::get_key() const {
    return _key;
}

void KeyboardEvent::set_type(KeyboardEvent::Type type) {
    _type = type;
}

void KeyboardEvent::set_key(KeyboardKey_t key) {
    _key = key;
}
