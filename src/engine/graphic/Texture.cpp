#include "Texture.h"

Texture::Texture(std::string name, int width, int height)
        : _name{std::move(name)}, _width{width}, _height{height} {
}

const std::string& Texture::get_name() const {
    return _name;
}

int Texture::get_width() const {
    return _width;
}

int Texture::get_height() const {
    return _height;
}
