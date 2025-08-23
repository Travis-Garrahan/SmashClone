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
    gravity = 0.5;
    velocity = Vector2{ 0.0f, 0.0f };
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

void Player::drawHitbox()
{
    DrawRectangleLines(static_cast<int>(hitbox.x),
        static_cast<int>(hitbox.y),
        static_cast<int>(hitbox.width),
        static_cast<int>(hitbox.height),
        RED);
}

void Player::changeState(PlayerState* newState)
{
    currentState = newState;
}

bool Player::isGrounded()
{
    const float playerBottomY = position.y + position.height;
    auto floorY = static_cast<float>(GetScreenHeight());

    if (playerBottomY >= floorY)
    {
        return true;
    }
    return false;
}

void Player::handleInput(Input input)
{
    currentState->handleInput(*this, input);
}

void Player::update(Input input)
{
    currentState->update(*this, input);

    velocity.y += gravity;
    position.y += velocity.y;

    // floor collision check
    auto floorY = static_cast<float>(GetScreenHeight());
    if (isGrounded())
    {
        position.y = floorY - position.height;
        velocity.y = 0;
    }
}



