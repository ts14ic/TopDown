#include "Circle.h"
#include "maths.h"

bool circles_collide(const Circle& lhs, const Circle& rhs) {
    float distance_between_circles = math::get_distance(
            lhs.get_center(),
            rhs.get_center()
    );
    float collision_distance = lhs.get_radius() + rhs.get_radius();
    return distance_between_circles < collision_distance;
}
