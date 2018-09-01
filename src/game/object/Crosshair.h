#pragma once

#include "engine/graphic/Graphic.h"
#include "Player.h"

class Crosshair {
public:
    enum class RenderType {
        NORMAL,
        RELOADING,
    };

    void handle_render(Graphic& graphic, RenderType renderType, int mouse_x, int mouse_y, float frames_count);

private:
    float _angle;
};
