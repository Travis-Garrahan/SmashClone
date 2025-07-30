//
// Created by travis on 7/9/25.
//

#include "player.h"

Player::Player(const char* textureFilePath, float _playerHeight, float _playerWidth, int _speed)
{
    texture = LoadTexture(textureFilePath);
    height = _playerHeight;
    width = _playerWidth;
    speed = _speed;
}

void Player::draw() const
{
    DrawTexture(texture, 100, 100 ,WHITE);
}

Texture2D Player::GetTexture() const
{
    return this->texture;
}

