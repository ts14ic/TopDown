#include "Damageable.h"

void Damageable::default_render_health(Graphic& graphic_context, const Color& color, float frames_count) const {
    if (get_hp() > 0) {
        Box healthBox;

        healthBox.set_size(50.f * get_hp() / get_default_hp(), 5.f);
        healthBox.set_left_top(
                get_position().x - healthBox.get_width() / 2 + get_current_speed().x * frames_count,
                get_position().y - get_circle().get_radius() + get_current_speed().y * frames_count
        );

        graphic_context.render_box(healthBox, color);
    }
}
