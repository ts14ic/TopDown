#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(Type type, KeyboardKey_t key) {
    _type = type;
    _key = key;
}

KeyboardEvent::Type KeyboardEvent::get_type() const {
    return _type;
}

KeyboardKey_t KeyboardEvent::get_key() const {
    return _key;
}
