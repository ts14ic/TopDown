#include "calculations.h"
#include "Circle.h"
#include <SDL_rect.h>

float pi() {
    return 3.14159265359f;
}

float rsin(float x) {
    return std::sin(x);
}

float rcos(float x) {
    return std::cos(x);
}

float dsin(float x) {
    return std::sin(to_rad(x));
}

float dcos(float x) {
    return std::cos(to_rad(x));
}

float to_rad(float angle) {
    return angle * pi()/180.f;
}

float to_deg(float angle) {
    return angle * 180.f/pi();
}

float rand_float(float range) {
    float k = (float) rand() / RAND_MAX;
    return range * (k * 2 - 1);
}

float get_distance(int ax, int ay, int bx, int by) {
    return std::hypot(bx - ax, by - ay);
}

float get_distance(SDL_Point const& a, SDL_Point const& b) {
    return get_distance(a.x, a.y, b.x, b.y);
}

float get_angle(int ax, int ay, int bx, int by) {
    return std::atan2(by - ay, bx - ax);
}

float get_angle(SDL_Point const& a, SDL_Point const& b) {
    return get_angle(a.x, a.y, b.x, b.y);
}

bool collides(SDL_Rect const& a, SDL_Rect const& b) {
    return SDL_HasIntersection(&a, &b);
}

bool collides(Circle const& a, SDL_Rect const& b) {
    SDL_Point c;

    if(a.getX() < b.x) {
        c.x = b.x;
    } else if(a.getX() > b.x + b.w) {
        c.x = b.x + b.w;
    }else{
        c.x = a.getX();
    }

    if(a.getY() < b.y) {
        c.y = b.y;
    } else if(a.getY() > b.y + b.w) {
        c.y = b.y + b.w;
    }else{
        c.y = a.getY();
    }

    return get_distance(a.getX(), a.getY(), c.x, c.y) < a.getRadius();
}

bool collides(SDL_Rect const& a, Circle const& b) {
    return collides(b, a);
}

bool collides(Circle const& a, Circle const& b) {
    return get_distance(a.getX(), a.getY(), b.getX(), b.getY()) < (a.getRadius() + b.getRadius());
}
