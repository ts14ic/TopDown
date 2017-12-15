//
// Created by ts14ic on 12/15/17.
//
#pragma once

class WindowEvent {
public:
    enum class Type {
        Close,
    };

    WindowEvent();

    Type getType() const;

    void setType(Type type);

private:
    Type mType;
};