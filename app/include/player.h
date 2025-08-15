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
    void changeState(PlayerState* newState);

    virtual void handleInput(Input input);
    virtual void update(Input input);


    AnimationHandler animationHandler;
    float height;
    float width;
    int speed;
    Rectangle position{};
    IdleState idleState;
    RunningState runningState;
    PlayerState* currentState;


private:

    Texture texture{};
};