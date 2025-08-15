//
// Created by travis on 8/15/25.
//
#include "player.h"
#include "states.h"

void IdleState::handleInput(Player& player, const Input input)
{
    if (input.isMoving())
    {
        player.changeState(&player.runningState);
    }
}

void IdleState::update(Player& player, const Input input)
{
    player.animationHandler.setCurrentAnimation("idle");
}

void RunningState::handleInput(Player& player, const Input input)
{
    if (!input.isMoving())
    {
        player.changeState(&player.idleState);
    }
}

void RunningState::update(Player& player, const Input input)
{
    player.animationHandler.setCurrentAnimation("running");

    if (input.moveLeft) player.position.x -= static_cast<float>(player.speed) * GetFrameTime();
    if (input.moveRight) player.position.x += static_cast<float>(player.speed) * GetFrameTime();
}