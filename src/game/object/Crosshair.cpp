#include "Crosshair.h"

void Crosshair::handle_render(Graphic& graphic, RenderType renderType, int mouse_x, int mouse_y, float frames_count) {
    auto texture = graphic.get_texture(renderType == RenderType::RELOADING
                                       ? "reload"
                                       : "crosshair");

    int x = mouse_x - texture.get_width() / 2;
    int y = mouse_y - texture.get_height() / 2;

    _angle += 5.f * frames_count;
    if (_angle > 360.f) {
        _angle = 5.f;
    }

    graphic.render_texture(texture.get_name(), x, y, _angle);
}
