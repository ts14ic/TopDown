#include "Damageable.h"

void Damageable::default_render_health(Graphic& graphic_context, const Color& color, float frames_count) const {
    if (get_hp() > 0) {
        Box healthBox;

        healthBox.set_sizes(50.f * get_hp() / get_default_hp(), 5);
        healthBox.set_position(
                get_position().x - healthBox.get_width() / 2 + get_current_x_speed() * frames_count,
                get_position().y - get_circle().get_radius() + get_current_y_speed() * frames_count
        );

        graphic_context.render_box(healthBox, color);
    }
}
