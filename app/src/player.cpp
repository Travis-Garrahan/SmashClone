//
// Created by travis on 7/9/25.
//
#include "player.h"

Player::Player(const char* textureFilePath,
    const char* animationJSONpath,
    const float _playerHeight,
    const float _playerWidth,
    const int _speed,
    const Rectangle _position)
    : animationHandler(animationJSONpath)
{
    texture = LoadTexture(textureFilePath);
    height = _playerHeight;
    width = _playerWidth;
    speed = _speed;
    position = _position;
    state_ = nullptr;
}

void Player::drawPlayer() const
{
    animationHandler.drawAnimation(texture, position);
}

void Player::handleInput(Input input)
{
    state_->handleInput(*this, input);
}

void Player::update()
{
    state_->update(*this);
}



