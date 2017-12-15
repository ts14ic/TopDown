//
// Created by ts14ic on 12/15/17.
//

#pragma once

class KeyboardEvent {
public:
    enum class Type {
        KeyDown,
        KeyUp,
    };

    KeyboardEvent();

    Type getType() const;

    int getKey() const;

    void setType(Type type);

    void setKey(int key);

private:
    Type mType;
    int mKey;
};
