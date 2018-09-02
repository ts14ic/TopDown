#pragma once

#include "Texture.h"
#include <engine/geometry/Box.h>
#include <engine/geometry/Color.h>
#include <stdexcept>
#include <iosfwd>

class Graphic {
public:
    virtual ~Graphic() = 0;

    virtual void refresh_screen() = 0;

    virtual void clear_screen() = 0;

    virtual void render_box(const Box& box, const Color& color) = 0;

    virtual void render_texture(const std::string& texture_name, Point2<int> position) = 0;

    virtual void render_texture(const std::string& texture_name, Point2<int> position, float angle) = 0;

    virtual void load_texture(const std::string& name, const char* path) = 0;

    struct FailedToLoadTextureException : public std::runtime_error {
        explicit FailedToLoadTextureException(const char* message);
    };

    virtual Texture get_texture(const std::string& name) = 0;

    virtual int get_screen_width() = 0;

    virtual int get_screen_height() = 0;
};