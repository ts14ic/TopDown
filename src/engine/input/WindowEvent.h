#pragma once

class WindowEvent {
public:
    enum class Type {
        CLOSE,
    };

    explicit WindowEvent(Type type);

    Type get_type() const;

private:
    Type _type;
};