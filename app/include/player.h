//
// Created by travis on 7/9/25.
//

#pragma once
#include <raylib.h>
#include "animation.h"
#include "input.h"
#include <fstream>

enum class PlayerStateName
{
    Idle,
    Running,
    Jumping,
    Attacking,
};

inline std::unordered_map<std::string, PlayerStateName> stringToState = {
    {"idle", PlayerStateName::Idle},
    {"running", PlayerStateName::Running},
    {"jumping", PlayerStateName::Jumping},
    {"attacking", PlayerStateName::Attacking}
};

class Player;

class PlayerState
{
public:
    virtual ~PlayerState() {}
    virtual void handleInput(Player& player, Input input) {}
    virtual void update(Player& player, Input input) {}
};

class Player
{
public:
    Player(const char *animationJSONpath, float _playerHeight, float _playerWidth, int _speed, Rectangle _position);
    void drawPlayer() const;
    void changeState(PlayerStateName newState);

    virtual ~Player() = default;
    virtual void handleInput(Input input);
    virtual void update(Input input);

    AnimationHandler animationHandler;
    float height;
    float width;
    int speed;
    Rectangle position;

private:
    Texture texture{};
    std::unordered_map<PlayerStateName, std::string> texturePath;
    PlayerState* state_;
};

class IdleState : public PlayerState
{
public:
    void handleInput(Player& player, Input input) override
    {
        if (input.isMoving())
        {
            player.changeState(PlayerStateName::Running);
        }
    };
    void update(Player& player, Input input) override
    {
        player.animationHandler.setCurrentAnimation("idle");
    };
};

class RunningState : public PlayerState
{
public:
    void handleInput(Player& player, Input input) override
    {
        if (!input.isMoving())
        {
            player.changeState(PlayerStateName::Idle);
        }
    }
    void update(Player& player, Input input) override
    {
        player.animationHandler.setCurrentAnimation("running");

        if (input.moveLeft) player.position.x -= static_cast<float>(player.speed) * GetFrameTime();
        if (input.moveRight) player.position.x += static_cast<float>(player.speed) * GetFrameTime();
    }
};


