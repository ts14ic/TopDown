#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Texture.h"
#include "calculations.h"
#include <vector>
#include <memory>

class Object {
public:
    virtual float x() const = 0;
    virtual float y() const = 0;
    virtual float angle() const = 0;
    virtual float speed() const = 0;
    
    virtual void x(float v) = 0;
    virtual void y(float v) = 0;
    virtual void angle(float a) = 0;
    virtual void speed(float s) = 0;
    
    virtual std::string texName() const = 0;

protected:
    void default_move() {
        x(x() + speed() * dcos(angle()));
        y(y() + speed() * dsin(angle()));
    }
    
    void default_render() {
        Texture& tex = textures(texName());
        int tx = x() - tex.w() / 2;
        int ty = y() - tex.h() / 2;
        tex.render(tx, ty, angle());
    }
};

class Player : public Object {
public:
    Player(int x, int y);

    float x() const;
    float y() const;
    float angle() const;
    float speed() const;
    
    void x(float x);
    void y(float y);
    void angle(float a);
    void speed(float s);
    
    std::string texName() const;
    
    void handle_events();
    void handle_logic();
    void handle_render();
private:
    float _x, _y, _speed = 2.f;
    float _angle = 0.0f;
    
    enum {
        IDLE        = 0x0,
        MOVES_UP    = 0x1,
        MOVES_DOWN  = 0x2,
        MOVES_LEFT  = 0x4,
        MOVES_RIGHT = 0x8
    };
    int _state = IDLE;
    
    std::string _tex = "player_pistol";
};

#endif
