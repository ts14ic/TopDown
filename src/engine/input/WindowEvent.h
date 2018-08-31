#pragma once

class WindowEvent {
public:
    enum class Type {
        Close,
    };

    WindowEvent();

    Type get_type() const;

    void set_type(Type type);

private:
    Type mType;
};