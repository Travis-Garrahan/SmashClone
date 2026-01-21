//
// Created by travis on 8/15/25.
//
#include "player.h"
#include "states.h"
#include <nlohmann/json.hpp>
#include <raymath.h>
#include <fstream>

void IdleState::onEnter(Player& player)
{
    player.animationHandler.setCurrentAnimation("idle");
    player.velocity.x = 0;
}

void IdleState::handleInput(Player& player, const Input input)
{
    DrawText(TextFormat("In Idle state"), 100, 100, 50, BLACK);
    if (input.jumpKeyPressed()) {
        player.changeState(&player.jumpingState);
    }

    else if (input.movementKeyPressed()) {
        player.changeState(&player.runningState);
    }

    else if (input.attackKeyPressed()) {
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
    if (!input.movementKeyPressed() && player.velocity.x == 0) {
        player.changeState(&player.idleState);
    }

    if (input.moveLeft) {
        player.facingDirection = Player::FacingDirection::LEFT;
    }
    else if (input.moveRight) {
        player.facingDirection = Player::FacingDirection::RIGHT;
    }
    if (input.jumpKeyPressed()) {
        player.changeState(&player.jumpingState);
    }
}

void RunningState::update(Player& player, const Input input)
{
    DrawText(TextFormat("Running state"), 100, 100, 50, BLACK);

    if (input.moveLeft) {
        if (player.velocity.x > player.speed) {
            player.velocity.x = player.speed;
        }
        else {
            player.velocity.x = player.velocity.x + player.speed * player.acceleration * GetFrameTime();
        }
    }

    if (input.moveRight) {
        if (player.velocity.x > player.speed) {
            player.velocity.x = player.speed;
        }
        else {
            player.velocity.x = player.velocity.x + player.speed * player.acceleration * GetFrameTime();
        }
    }

    if (!input.movementKeyPressed() && player.velocity.x > 0) {
        // dampen velocity
        player.velocity.x *= 0.9;

        if (player.velocity.x > 0.1) {
            player.velocity.x = 0;
        }
    }
}

void JumpingState::onEnter(Player& player)
{
    player.animationHandler.setCurrentAnimation("jumpsquat");


    leftGround = false;
    inJumpSquat = true;
    appliedImpulse = false;
    jumpState = jumpsquat;

    if (jumpFrameCounter == -1)
        jumpFrameCounter = 0;
}

void JumpingState::handleInput(Player& player, const Input input)
{
    if (input.moveLeft) {
        if (player.velocity.x > 0) {
            player.airSpeed *= 0.25f;
        }
        player.velocity.x -= player.airSpeed;
    }
    if (input.moveRight) {
        if (player.velocity.x < 0) {
            player.airSpeed *= 0.25f;
        }
        player.velocity.x += player.airSpeed;
    }

    player.velocity.x = Clamp(
        player.velocity.x,
        -player.maxAirSpeed,
        player.maxAirSpeed
    );
}

void JumpingState::update(Player& player, const Input input)
{
    DrawText(TextFormat("In Jumping State"), 100 , 100, 50, BLACK);
    DrawText(TextFormat("JumpSquat: %d", inJumpSquat), 100, 150, 50, BLACK);



    if (jumpFrameCounter >= 0) {
        jumpFrameCounter++;
    }

    if (jumpFrameCounter >= jumpDelayFrames) {
        inJumpSquat = false;

        if (jumpState == jumpsquat && player.animationHandler.isAnimationFinished()) {
            player.animationHandler.setCurrentAnimation("takeoff");
            jumpState = takeoff;
        }

        if (jumpState == takeoff && player.animationHandler.isAnimationFinished()) {
            player.animationHandler.setCurrentAnimation("falling");
            jumpState = falling;
        }
    }

    if (jumpState == jumpsquat && !appliedImpulse) {
        player.velocity.y = -20;
        appliedImpulse = true;
        return; // <--- prevents ground check from occurring on same frame of leaving ground
    }

    if (!leftGround) {
        if (!player.isGrounded())
            leftGround = true;
         return; // still on takeoff frame
    }

    if (player.isGrounded() && jumpState != landing) {
        jumpState = landing;
        player.animationHandler.setCurrentAnimation("landing");
    }

    if (jumpState == landing) {
        if (player.animationHandler.isAnimationFinished()) {
            player.changeState(&player.idleState);
        }
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
        player.animationHandler.currentAnimation->currentFrame < player.attackEndActiveFrame) {
        player.hitbox.isActive = true;
    }
    else
    {
        player.hitbox.isActive = false;
    }

    if (player.hitbox.isActive){
        DrawText(TextFormat("Hitbox active"), 100, 200, 50, BLACK);
        DrawRectangle(player.hitbox.position.x, player.hitbox.position.y, player.hitbox.width, player.hitbox.height, GREEN);
    }

    if (player.animationHandler.isAnimationFinished()){
        player.hitbox.isActive = false;
        player.changeState(&player.idleState);
    }
}

