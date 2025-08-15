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
    virtual void update(Player& player) {}
};

class Player
{
public:
    Player(const char *animationJSONpath, float _playerHeight, float _playerWidth, int _speed, Rectangle _position);
    void drawPlayer() const;
    void changeState(PlayerStateName newState);

    virtual ~Player() {}
    virtual void handleInput(Input input);
    virtual void update();

    AnimationHandler animationHandler;
    float height;
    float width;
    int speed;
    Rectangle position;

private:
    Texture texture{};
    std::unordered_map<PlayerStateName, std::string> texturePaths;
    PlayerState* state_;
};

class IdleState : public PlayerState
{
public:
    void handleInput(Player& player, Input input) override;
    void update(Player& player) override;
};

class RunningState : public PlayerState
{
public:
    void handleInput(Player& player, Input input) override;
    void update(Player& player) override;
};


