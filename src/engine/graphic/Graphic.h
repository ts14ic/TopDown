#pragma once

#include "Box.h"
#include "Color.h"
#include <iosfwd>

class Graphic {
public:
    virtual ~Graphic() = 0;

    virtual void refresh_screen() = 0;

    virtual void clear_screen() = 0;

    virtual void render_box(const Box& box, const Color& color) = 0;

    virtual void render(const std::string& texture_name, int x, int y) = 0;

    virtual void render(const std::string& texture_name, int x, int y, float angle) = 0;

    virtual void load_texture(const std::string& name, const char* path) = 0;

    virtual int get_texture_width(const std::string& name) = 0;

    virtual int get_texture_height(const std::string& name) = 0;

    virtual int get_screen_width() = 0;

    virtual int get_screen_height() = 0;
};