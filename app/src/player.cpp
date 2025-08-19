//
// Created by travis on 7/9/25.
//
#include "player.h"
#include "states.h"
#include <fstream>

Player::Player(
               const char* animationJSONpath,
               const float _playerHeight,
               const float _playerWidth,
               const int _speed,
               const Rectangle _position)
    : animationHandler(animationJSONpath),
    currentState(&idleState)
{
    std::ifstream file("assets/attributes/player_animation_data.json");
    nlohmann::json j;
    file >> j;

    const auto& atlasPath = j["redman"]["atlas"].get<std::string>();

    facingDirection = FacingDirection::RIGHT;
    texture = LoadTexture(atlasPath.c_str());
    height = _playerHeight;
    width = _playerWidth;
    speed = _speed;
    position = _position;


}


void Player::drawPlayer() const
{
    Rectangle src = animationHandler.currentAnimation->getFrameRec();
    Rectangle dest = position;

    if (facingDirection == FacingDirection::RIGHT)
    {
        DrawTexturePro(texture, src, dest, {0,0}, 0.0f, WHITE);
    }
    else
    {
        src.width = -src.width;
        DrawTexturePro(texture, src, dest, {0,0}, 0.0f, WHITE);
    }
}

void Player::changeState(PlayerState* newState)
{
    currentState = newState;
}

void Player::handleInput(Input input)
{
    currentState->handleInput(*this, input);
}

void Player::update(Input input)
{
    currentState->update(*this, input);
}



