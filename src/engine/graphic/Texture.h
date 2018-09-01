#pragma once

#include <string>

// TODO Add a fallback texture

class Texture {
public:
    Texture(std::string name, int width, int height);

    const std::string& get_name() const;

    int get_width() const;

    int get_height() const;

private:
    std::string _name;
    int _width;
    int _height;
};
