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
    Player(const char *textureFilePath, const char *animationJSONpath, float _playerHeight, float _playerWidth, int _speed, Rectangle _position);
    void drawPlayer() const;

    [[nodiscard]] Texture2D GetTexture() const;
    [[nodiscard]] PlayerState GetState() const;
    // set state depending on input
    // void SetState(PlayerState state);

    AnimationHandler animationHandler;
    float height;
    float width;
    int speed;
    Rectangle position;

private:
    Texture texture{};
    PlayerState state;
};


