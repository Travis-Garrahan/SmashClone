//
// Created by travis on 7/9/25.
//

#pragma once
#include <raylib.h>
#include "animation.h"
#include "input.h"
#include "states.h"


class Player
{
public:
    Player(const char *animationJSONpath, float _playerHeight, float _playerWidth, int _speed, Rectangle _position);
    virtual ~Player() = default;
    void drawPlayer() const;
    void drawHitbox();
    void changeState(PlayerState* newState);
    enum class FacingDirection{RIGHT,LEFT,};
    bool isGrounded();

    virtual void handleInput(Input input);
    virtual void update(Input input);


    AnimationHandler animationHandler;
    FacingDirection facingDirection;
    float height;
    float width;
    int speed;
    Vector2 velocity;
    float gravity;

    Rectangle position{};
    IdleState idleState;
    RunningState runningState;
    JumpingState jumpingState;
    PlayerState* currentState;

    Rectangle hitbox{};

private:
    Texture texture{};
};