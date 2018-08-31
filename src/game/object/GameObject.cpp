#include "GameObject.h"

bool objects_collide(GameObject &a, GameObject &b) {
    return circles_collide(a.get_circle(), b.get_circle());
}

void GameObject::default_move() {
    set_x(get_x() + get_current_speed_x());
    set_y(get_y() + get_current_speed_y());
}

void GameObject::default_render(Engine &resources, GraphicContext &graphicContext, float predictionRatio) {
    Texture& tex = resources.get_texture(get_tex_name());

    auto x = get_x() - tex.get_width() / 2;
    auto predicted_dx = get_current_speed_x() * predictionRatio;

    auto y = get_y() - tex.get_height() / 2;
    auto predicted_dy = get_current_speed_y() * predictionRatio;

    graphicContext.render(
            tex,
            static_cast<int>(x + predicted_dx),
            static_cast<int>(y + predicted_dy),
            get_angle()
    );
}
