#include "Damageable.h"

void
Damageable::default_render_health(Graphic& graphic_context, const Color& color, float prediction_ratio) const {
    if (get_hp() > 0) {
        Box healthBox;

        healthBox.set_sizes(50.f * get_hp() / get_default_hp(), 5);
        healthBox.set_position(
                get_x() - healthBox.get_width() / 2 + get_current_x_speed() * prediction_ratio,
                get_y() - get_circle().get_radius() + get_current_y_speed() * prediction_ratio
        );

        graphic_context.render_box(healthBox, color);
    }
}
