//
// Created by travis on 7/9/25.
//

#include "player.h"

Player::Player(const char* textureFilePath, const float initPosX, const float initPosY)
{
    texture = LoadTexture(textureFilePath);
    posX = initPosX;
    posY = initPosY;
    speed = 0;
}

void Player::DrawPlayer() const
{
    auto textureRect = (Rectangle){0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    auto destRect = (Rectangle){posX, posY, 300, 300};
    DrawTexturePro(texture, textureRect, destRect, (Vector2){0, 0,}, 0.0f, WHITE);
}
