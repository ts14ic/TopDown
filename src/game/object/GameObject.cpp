#include "GameObject.h"

bool objects_collide(GameObject& a, GameObject& b) {
    return circles_collide(a.get_circle(), b.get_circle());
}

void GameObject::default_move() {
    set_x(get_x() + get_current_x_speed());
    set_y(get_y() + get_current_y_speed());
}

void GameObject::default_render(Graphic& graphic, float frames_count) {
    auto texture = graphic.get_texture(get_tex_name());

    auto x = get_x() - texture.get_width() / 2;
    auto predicted_dx = get_current_x_speed() * frames_count;

    auto y = get_y() - texture.get_height() / 2;
    auto predicted_dy = get_current_y_speed() * frames_count;

    graphic.render_texture(
            texture.get_name(),
            static_cast<int>(x + predicted_dx),
            static_cast<int>(y + predicted_dy),
            get_angle()
    );
}
