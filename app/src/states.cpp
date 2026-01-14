//
// Created by travis on 8/15/25.
//
#include "player.h"
#include "states.h"
#include <nlohmann/json.hpp>
#include <fstream>

void IdleState::onEnter(Player& player)
{
    player.animationHandler.setCurrentAnimation("idle");
}

void IdleState::handleInput(Player& player, const Input input)
{
    DrawText(TextFormat("In Idle state"), 100, 100, 50, BLACK);
    if (input.jumpKeyPressed())
    {
        player.changeState(&player.jumpingState);
    }

    else if (input.movementKeyPressed())
    {
        player.changeState(&player.runningState);
    }

    else if (input.attackKeyPressed())
    {
        player.changeState(&player.attackingState);
    }



}

void IdleState::update(Player& player, const Input input)
{
    player.animationHandler.updateAnimation();
}


void RunningState::onEnter(Player& player)
{
    player.animationHandler.setCurrentAnimation("running");
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
    if (input.jumpKeyPressed())
    {
        player.changeState(&player.jumpingState);
    }
}

void RunningState::update(Player& player, const Input input)
{
    DrawText(TextFormat("Running state"), 100, 100, 50, BLACK);
    if (input.moveLeft) player.position.x -= static_cast<float>(player.speed) * GetFrameTime();
    if (input.moveRight) player.position.x += static_cast<float>(player.speed) * GetFrameTime();
}



void JumpingState::onEnter(Player& player)
{
}

void JumpingState::handleInput(Player& player, const Input input)
{

}

void JumpingState::update(Player& player, const Input input)
{
    DrawText(TextFormat("In Jumping State"), 100 , 100, 50, BLACK);

    if (!appliedImpulse)
    {
        player.velocity.y = -20;
        appliedImpulse = true;
        return; // <--- prevents ground check from occurring on same frame of leaving ground
    }

    if (!leftGround)
    {
        if (!player.isGrounded())
            leftGround = true;
         return; // still on takeoff frame
    }

    if (player.isGrounded())
    {
        appliedImpulse = false;
        player.changeState(&player.idleState);
    }
}


void AttackingState::onEnter(Player& player)
{
    player.animationHandler.setCurrentAnimation("punching");
    
    float hitBoxOffsetX = player.width / 4 + 50;

    player.hitbox.position.x = player.position.x + hitBoxOffsetX;
    player.hitbox.position.y = player.position.y + player.height / 4;
}

void AttackingState::handleInput(Player& player, const Input input)
{

}

void AttackingState::update(Player& player, const Input input)
{
    DrawText(TextFormat("Attacking state"), 100, 100, 50, BLACK);
    DrawText(TextFormat("Frames: %d", player.animationHandler.currentAnimation->currentFrame), 150, 150, 50, BLACK);


    // activate hitbox
    if (player.animationHandler.currentAnimation->currentFrame >= player.attackStartActiveFrame &&
        player.animationHandler.currentAnimation->currentFrame < player.attackEndActiveFrame)
    {
        player.hitbox.isActive = true;
    }
    else
    {
        player.hitbox.isActive = false;
    }



    if (player.hitbox.isActive)
    {
        DrawText(TextFormat("Hitbox active"), 100, 200, 50, BLACK);
        DrawRectangle(player.hitbox.position.x, player.hitbox.position.y, player.hitbox.width, player.hitbox.height, GREEN);
    }

    if (player.animationHandler.isAnimationFinished())
    {
        player.hitbox.isActive = false;
        player.changeState(&player.idleState);
    }
}

