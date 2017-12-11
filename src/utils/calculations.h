#pragma once

struct SDL_Point;
struct SDL_Rect;

class Circle;

// trigonometry
float pi();

float to_rad(float angle);
float to_deg(float angle);

float rcos(float x);
float rsin(float x);
float dcos(float x);
float dsin(float x);

float rand_float(float range);

float get_distance(int ax, int ay, int bx, int by);
float get_distance(SDL_Point const& a, SDL_Point const& b);

float get_angle(int ax, int ay, int bx, int by);
float get_angle(SDL_Point const& a, SDL_Point const& b);

bool collides(SDL_Rect const& a, SDL_Rect const& b);
bool collides(Circle const& a, SDL_Rect const& b);
bool collides(SDL_Rect const& a, Circle const& b);
bool collides(Circle const& a, Circle const& b);
