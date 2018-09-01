#include "Circle.h"
#include "math/maths.h"

bool circles_collide(const Circle& lhs, const Circle& rhs) {
    float distance_between_circles = math::get_distance(
            lhs.get_center().x,
            lhs.get_center().y,
            rhs.get_center().x,
            rhs.get_center().y
    );
    float collision_distance = lhs.get_radius() + rhs.get_radius();
    return distance_between_circles < collision_distance;
}
