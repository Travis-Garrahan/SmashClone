//
// Created by travis on 7/9/25.
//
#include "player.h"

Player::Player(
               const char* animationJSONpath,
               const float _playerHeight,
               const float _playerWidth,
               const int _speed,
               const Rectangle _position)
    : animationHandler(animationJSONpath)
{
    std::ifstream file("assets/attributes/player_animation_data.json");
    nlohmann::json j;
    file >> j;

    for (auto& [stateName, data]: j.items())
    {
        texturePaths[stringToState[stateName]] = data["atlas"].get<std::string>();
    }

    texture = LoadTexture(texturePaths.at(PlayerStateName::Idle).c_str());
    height = _playerHeight;
    width = _playerWidth;
    speed = _speed;
    position = _position;
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



