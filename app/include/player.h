//
// Created by travis on 7/9/25.
//

#pragma once
#include <raylib.h>
#include "animation.h"

// TODO: Implement player state classes
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
    Player(const char *textureFilePath, float _playerHeight, float _playerWidth, int _speed);
    void draw() const;
    Texture2D GetTexture() const;
    float height;
    float width;
    int speed;
private:
    // TODO: Implement PlayerState member and Animation hashmap.
    Texture texture{};

};


