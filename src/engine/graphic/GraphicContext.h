#pragma once

#include "Texture.h"
#include "Box.h"
#include "Color.h"

class GraphicContext {
public:
    virtual ~GraphicContext() = 0;

    virtual void refresh_screen() = 0;

    virtual void clear_screen() = 0;

    virtual void render_box(const Box &box, const Color &color) = 0;

    virtual void render(Texture const& texture, int x, int y) = 0;

    virtual void render(Texture const& texture, int x, int y, float angle) = 0;

    virtual int get_screen_width() = 0;

    virtual int get_screen_height() = 0;
};