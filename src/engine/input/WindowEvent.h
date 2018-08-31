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