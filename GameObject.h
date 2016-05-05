#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Texture.h"
#include "calculations.h"
#include "StopWatch.h"
#include <vector>
#include <memory>

/* forward declarations begin */
struct SDL_Color;
/* forward declarations end */

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
    
    virtual Circle circle() const = 0;
    
    bool collides(Object const& other) {
        return ::collides(circle(), other.circle());
    }
    
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

class Damageable : public virtual Object {
public:
    virtual int hp() const = 0;
    virtual int defaultHp() const = 0;

    virtual int dmg() const = 0;
    virtual void damage(int v) = 0;
    
    virtual bool dead() const = 0;
protected:
    void default_render_health(SDL_Color const& c) const;
};

class Weapon;

class Bullet : public Object {
public:
    Bullet(Object const& origin, Weapon const& weap);

    float x() const;
    float y() const;
    float angle() const;
    float speed() const;
    
    void x(float x);
    void y(float y);
    void angle(float a);
    void speed(float s);
    
    Circle circle() const;
    
    std::string texName() const;
    
    int dmg() const;
    
    void handle_logic();
    void handle_render();
    
private:
    int _dmg;
    float _x, _y, _angle, _speed;
};

std::vector<Bullet>& bullets();

enum EWeapon {
    WEAPON_PISTOL,
    WEAPON_SHOTGUN,
    WEAPON_UZI,
    WEAPON_LAST = WEAPON_SHOTGUN,
    WEAPON_TOTAL
};

class Weapon {
public:
    virtual void  shoot(Object const& shooter) = 0;
    virtual int   length() const = 0;
    virtual int   dmg() const = 0;
    virtual float speed() const = 0;
    virtual float spread() const = 0;
    virtual bool  reloading() const = 0;
    virtual void  reload() = 0;
protected:
    int _ammo;
    int _speed;
    int _dmg;
};

class Pistol : public Weapon {
public:
    Pistol();

    void shoot(Object const& shooter);
    int   dmg()    const;
    float speed()  const;
    int   length() const;
    float spread() const;
    bool  reloading() const;
    void  reload();
private:
    StopWatch _cd;
    StopWatch _reload;
    
    bool _reloading = false;
    int _magAmmo = 7;
};

class Shotgun : public Weapon {
public:
    Shotgun();
    
    void shoot(Object const& shooter);
    int   dmg()    const;
    float speed()  const;
    int   length() const;
    float spread() const;
    bool  reloading() const;
    void  reload();
private:
    StopWatch _cd;
    StopWatch _reload;
    
    bool _reloading = false;
    int _magAmmo = 2;
};

class Player : public virtual Object, public Damageable {
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
    
    Circle circle() const;
    
    std::string texName() const;
    
    int hp() const;
    int defaultHp() const;
    int dmg() const;
    bool dead() const;
    void damage(int v);
    
    void handle_events();
    void handle_logic();
    void handle_render();
private:
    float _x, _y, _speed = 2.f;
    float _angle = 0.0f;
    
    std::unique_ptr<Weapon> _weapons[WEAPON_TOTAL];
    int _currentWeap = WEAPON_PISTOL;
    int _hp;
    
    StopWatch _dmgCd;
    
    enum {
        IDLE        = 0x0,
        MOVES_UP    = 0x1,
        MOVES_DOWN  = 0x2,
        MOVES_LEFT  = 0x4,
        MOVES_RIGHT = 0x8,
        SHOOTS      = 0x10
    };
    int _state = IDLE;
};

class Zombie : public Damageable{
public:
    Zombie(int x, int y);

    // Object legacy
    float x() const;
    float y() const;
    void x(float x);
    void y(float y);
    
    float angle() const;
    float speed() const;
    void angle(float a);
    void speed(float s);
    
    Circle circle() const;
    
    std::string texName() const;
    
    // Damageable legacy
    int        hp() const;
    int defaultHp() const;
    bool     dead() const;
    int    dmg() const;
    void damage(int d);
    
    // StateMoon interface
    void set_target(float x, float y, bool ignore = false);
    void handle_logic();
    void handle_render();
private:
    float _x, _y;
    float _angle;
    float _speed = 1.7f;
    
    int _hp, _frame = 0;
    
    StopWatch _timer;
    
    enum {
        IDLE      = 0x0,
        MOVING    = 0x1,
        ATTACKING = 0x2,
        DYING     = 0x4
    };
    int _state = IDLE;
};

std::vector<Zombie>& zombies();

#endif
