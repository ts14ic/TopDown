#include "Damageable.h"

void Damageable::default_render_health(Graphic& graphic, const Color& color, float frames_count) const {
    if (has_hp()) {
        Box health_box;

        health_box.set_size(50.f * get_hp() / get_default_hp(), 5.f);
        health_box.set_left_top(
                get_position().x - health_box.get_width() / 2 + get_current_speed().x * frames_count,
                get_position().y - get_circle().get_radius() + get_current_speed().y * frames_count
        );

        graphic.render_box(health_box, color);
    }
}
