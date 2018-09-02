#pragma once

#include <iosfwd>

class HasTexture {
public:
    virtual std::string get_tex_name() const = 0;
};