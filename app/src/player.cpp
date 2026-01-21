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
               const float _speed,
               const Rectangle _position)
    : animationHandler(animationJSONpath),
    currentState(&idleState)
{
    std::ifstream file("assets/attributes/player_animation_data.json");
    nlohmann::json j = nlohmann::json::parse(file);

    const auto& atlasPath = j["redman"]["atlas"].get<std::string>();

    facingDirection = FacingDirection::RIGHT;
    texture = LoadTexture(atlasPath.c_str());
    height = _playerHeight;
    width = _playerWidth;
    gravity = 0.5;
    velocity = Vector2{ 0.0f, 0.0f };
    speed = _speed;
    airSpeed = 5.0f;
    maxAirSpeed = 500;
    acceleration = 7;
    position = _position;
    attackStartActiveFrame = j["redman"]["attacks"][0]["activeStartFrame"].get<int>();
    attackEndActiveFrame = j["redman"]["attacks"][0]["activeEndFrame"].get<int>();
    hitbox = { false, Vector2(position.x, position.y), 25, 25 };
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
    if (currentState == newState) return;

    currentState = newState;
    currentState->onEnter(*this);
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

    if (input.moveLeft) {
        position.x -= velocity.x * GetFrameTime();
    }

    if (input.moveRight) {
        position.x += velocity.x * GetFrameTime();
    }


    // floor collision check
    auto floorY = static_cast<float>(GetScreenHeight());
    if (isGrounded()) {
        position.y = floorY - position.height;
        velocity.y = 0;
    }
}



