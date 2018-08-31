#pragma once

#include "Damageable.h"
#include "Weapon.h"
#include "engine/Timer.h"
#include "engine/input/InputContext.h"
#include <memory>
#include <bitset>

class Player : public virtual GameObject,
               public Damageable,
               public KeyboardEventHandler,
               public MouseEventHandler {
public:
    Player();

    Player(int x, int y);

    float getX() const override;

    float getY() const override;

    float getAngle() const override;

    float getMaxMovementSpeed() const override;

    float getCurrentSpeedX() const override;

    float getCurrentSpeedY() const override;

    void setPos(float x, float y) override;

    void setX(float x) override;

    void setY(float y) override;

    void setAngle(float a) override;

    void setMaxMovementSpeed(float movementSpeed) override;

    void setCurrentSpeedX(float speedX) override;

    void setCurrentSpeedY(float speedY) override;

    void setCurrentSpeed(float speedX, float speedY) override;

    Circle getCircle() const override;

    std::string getTexName() const override;

    int hp() const override;

    int defaultHp() const override;

    int dmg() const override;

    bool dead() const override;

    void damage(const Clock& clock, int damageAmount) override;

    bool reloading() const;

    void handleKeyEvent(const KeyboardEvent& event) override;

    void handleMouseEvent(const MouseEvent& event) override;

    void handle_logic(Random& random, Resources& resources, AudioContext& audioContext);

    void handleRender(Resources& resources, GraphicContext& graphicContext, float predictionRatio);

    void addWeapon(Weapon weapon);

private:
    void selectNextWeapon();

    void selectPreviousWeapon();

    void selectWeapon(unsigned idx);

private:
    void setSpeeds();

private:
    float mX = 0;
    float mY = 0;
    float mCurrentSpeedX = 0;
    float mCurrentSpeedY = 0;
    float mMaxMovementSpeed = 0;
    float mAngle = 0.0f;

    std::vector<Weapon> mWeapons;
    unsigned mSelectedWeaponIdx = 0;
    int _hp = 0;

    Timer mDamageCooldown;

    enum InputState {
        UP_PRESSED,
        DOWN_PRESSED,
        LEFT_PRESSED,
        RIGHT_PRESSED,
        TRIGGER_PRESSED,
        LENGTH
    };
    std::bitset<LENGTH> mInputState;
};