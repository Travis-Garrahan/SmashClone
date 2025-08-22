//
// Created by travis on 8/15/25.
//
#include "player.h"
#include "states.h"

void IdleState::handleInput(Player& player, const Input input)
{
    if (input.movementKeyPressed())
    {
        player.changeState(&player.runningState);
    }

    if (input.jumpKeyPressed())
    {
        player.changeState(&player.jumpingState);
    }
}

void IdleState::update(Player& player, const Input input)
{
    player.animationHandler.setCurrentAnimation("idle");
}

void RunningState::handleInput(Player& player, const Input input)
{
    if (!input.movementKeyPressed())
    {
        player.changeState(&player.idleState);
    }
    if (input.moveLeft)
    {
        player.facingDirection = Player::FacingDirection::LEFT;
    }
    else if (input.moveRight)
    {
        player.facingDirection = Player::FacingDirection::RIGHT;
    }
}

void RunningState::update(Player& player, const Input input)
{
    player.animationHandler.setCurrentAnimation("running");

    if (input.moveLeft) player.position.x -= static_cast<float>(player.speed) * GetFrameTime();
    if (input.moveRight) player.position.x += static_cast<float>(player.speed) * GetFrameTime();
}

void JumpingState::handleInput(Player& player, const Input input)
{

}

void JumpingState::update(Player& player, const Input input)
{
    if (!appliedImpulse)
    {
        player.velocity.y = -20;
        appliedImpulse = true;
    }

    if (player.isGrounded())
    {
        appliedImpulse = false;
        player.changeState(&player.idleState);
    }
}