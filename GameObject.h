#pragma once

#include "Texture.h"
#include "calculations.h"
#include "StopWatch.h"
#include "engine/InputSystem.h"
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

    virtual std::string texName() const = 0;

protected:
    void default_move() {
        x(x() + speed() * dcos(angle()));
        y(y() + speed() * dsin(angle()));
    }

    void default_render(RenderSystem& engine) {
        Texture& tex = textures(texName());
        auto tx = static_cast<int>(x() - tex.w() / 2);
        auto ty = static_cast<int>(y() - tex.h() / 2);
        tex.render(engine, tx, ty, angle());
    }
};

bool objectsCollide(Object& a, Object& b);

class Damageable : public virtual Object {
public:
    virtual int hp() const = 0;

    virtual int defaultHp() const = 0;

    virtual int dmg() const = 0;

    virtual void damage(int v) = 0;

    virtual bool dead() const = 0;

protected:
    void default_render_health(RenderSystem& engine, SDL_Color const& c) const;
};

class Weapon;

class Bullet : public Object {
public:
    Bullet(Object const& origin, Weapon const& weap);

    float x() const override;

    float y() const override;

    float angle() const override;

    float speed() const override;

    void x(float x) override;

    void y(float y) override;

    void angle(float a) override;

    void speed(float s) override;

    Circle circle() const override;

    std::string texName() const override;

    int dmg() const;

    void handle_logic();

    void handle_render(RenderSystem& engine);

private:
    int _dmg;
    float _x, _y, _angle, _speed;
};

std::vector<Bullet>& bullets();

enum EWeapon {
    WEAPON_PISTOL,
    WEAPON_FIRST = WEAPON_PISTOL,
    WEAPON_SHOTGUN,
    WEAPON_UZI,
    WEAPON_LAST = WEAPON_UZI,
    WEAPON_TOTAL
};

class Weapon {
public:
    virtual void shoot(Object const& shooter) = 0;

    virtual int length() const = 0;

    virtual int dmg() const = 0;

    virtual float speed() const = 0;

    virtual float spread() const = 0;

    virtual bool reloading() const = 0;

    virtual void reload() = 0;
};

class Pistol : public Weapon {
public:
    Pistol();

    void shoot(Object const& shooter) override;

    int dmg() const override;

    float speed() const override;

    int length() const override;

    float spread() const override;

    bool reloading() const override;

    void reload() override;

private:
    StopWatch _cd;
    StopWatch _reload;

    bool _reloading = false;
    int _magAmmo = 7;
};

class Shotgun : public Weapon {
public:
    Shotgun();

    void shoot(Object const& shooter) override;

    int dmg() const override;

    float speed() const override;

    int length() const override;

    float spread() const override;

    bool reloading() const override;

    void reload() override;

private:
    StopWatch _cd;
    StopWatch _reload;

    bool _reloading = false;
    int _magAmmo = 2;
};

class Uzi : public Weapon {
public:
    Uzi();

    void shoot(Object const& shooter) override;

    int dmg() const override;

    float speed() const override;

    int length() const override;

    float spread() const override;

    bool reloading() const override;

    void reload() override;

private:
    StopWatch _cd;
    StopWatch _reload;

    bool _reloading = false;
    int _magAmmo = 25;
};

class Player : public virtual Object, public Damageable {
public:
    Player(int x, int y);

    float x() const override;

    float y() const override;

    float angle() const override;

    float speed() const override;

    void x(float x) override;

    void y(float y) override;

    void angle(float a) override;

    void speed(float s) override;

    Circle circle() const override;

    std::string texName() const override;

    int hp() const override;

    int defaultHp() const override;

    int dmg() const override;

    bool dead() const override;

    void damage(int v) override;

    bool reloading() const;

    void handle_events(InputSystem& input);

    void handle_logic();

    void handle_render(RenderSystem& engine);

private:
    float _x, _y, _speed;
    float _angle = 0.0f;

    std::unique_ptr<Weapon> _weapons[WEAPON_TOTAL];
    int _currentWeap = WEAPON_PISTOL;
    int _hp;

    StopWatch _dmgCd;

    enum {
        IDLE = 0x0,
        MOVES_UP = 0x1,
        MOVES_DOWN = 0x2,
        MOVES_LEFT = 0x4,
        MOVES_RIGHT = 0x8,
        SHOOTS = 0x10
    };
    int _state = IDLE;
};

class Zombie : public Damageable {
public:
    Zombie(int x, int y);

    // Object legacy
    float x() const override;

    float y() const override;

    void x(float x) override;

    void y(float y) override;

    float angle() const override;

    float speed() const override;

    void angle(float a) override;

    void speed(float s) override;

    Circle circle() const override;

    std::string texName() const override;

    // Damageable legacy
    int hp() const override;

    int defaultHp() const override;

    bool dead() const override;

    int dmg() const override;

    void damage(int d) override;

    // StateMoon interface
    void set_target(float x, float y, bool ignore = false);

    void handle_logic();

    void handle_render(RenderSystem& engine);

private:
    float _x, _y;
    float _angle;
    float _speed = 1.7f;

    int _hp, _frame = 0;

    StopWatch _timer;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        DYING = 0x4
    };
    int _state = IDLE;
};

std::vector<Zombie>& zombies();

class Werewolf : public Damageable {
public:
    Werewolf(float x, float y);

    // Object legacy
    float x() const override;

    float y() const override;

    void x(float x) override;

    void y(float y) override;

    float angle() const override;

    float speed() const override;

    void angle(float a) override;

    void speed(float s) override;

    Circle circle() const override;

    std::string texName() const override;

    // Damageable legacy
    int hp() const override;

    int defaultHp() const override;

    int dmg() const override;

    void damage(int d) override;

    bool dead() const override;

    // StateMoon interface
    void set_target(float x, float y, bool ignore = false);

    void teleport();

    void handle_logic();

    void handle_render(RenderSystem& engine);

private:
    float _x, _y, _speed = 2.5f;
    float _angle = 0.f;
    int _hp;

    int _frame = 0;
    StopWatch _timer;
    StopWatch _teleportCd;

    enum {
        IDLE = 0x0,
        MOVING = 0x1,
        ATTACKING = 0x2,
        TELEPORTING = 0x4,
        DYING = 0x8
    };
    int _state = IDLE;
};

std::vector<Werewolf>& werewolves();
