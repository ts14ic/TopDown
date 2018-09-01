#include "GameObject.h"

bool objects_collide(GameObject& a, GameObject& b) {
    return circles_collide(a.get_circle(), b.get_circle());
}

void GameObject::default_move() {
    set_position(
            get_position().x + get_current_speed().x,
            get_position().y + get_current_speed().y
    );
}

void GameObject::default_render(Graphic& graphic, float frames_count) {
    auto texture = graphic.get_texture(get_tex_name());

    auto point = make_point(
            get_position().x - texture.get_size().get_width() / 2.f,
            get_position().y - texture.get_size().get_height() / 2.f
    );
    point.x += get_current_speed().x * frames_count;
    point.y += get_current_speed().y * frames_count;

    graphic.render_texture(
            texture.get_name(),
            point_cast<int>(point),
            get_angle()
    );
}
