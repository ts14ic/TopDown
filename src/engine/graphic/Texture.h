#pragma once

#include <engine/geometry/Size2d.h>
#include <string>

// TODO Add a fallback texture

class Texture {
public:
    Texture(std::string name, Size2d<int> size) : _name{std::move(name)} {
        _size = size;
    }

    const std::string& get_name() const { return _name; }

    Size2d<int> get_size() const { return _size; }

private:
    std::string _name;
    Size2d<int> _size;
};
