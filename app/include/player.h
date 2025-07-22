//
// Created by travis on 7/9/25.
//

#pragma once
#include <raylib.h>
#include "animation.h"

enum PlayerState
{
    IDLE = 0,
    RUNNING = 1,
    JUMPING = 2,
    ATTACKING = 3
};

class Player
{
public:
    Texture texture;
    //PlayerState state;

    float height;
    float width;
    int speed;
   //Animation animations[]

    Player(const char *textureFilePath, float _playerHeight, float _playerWidth, int _speed);
    void draw() const;
};


