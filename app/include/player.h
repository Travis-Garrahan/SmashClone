//
// Created by travis on 7/9/25.
//

#pragma once
#include <raylib.h>
#include "animation.h"
#include "input.h"


class Player;
// TODO: Implement player state classes
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
    Player(const char *textureFilePath, const char *animationJSONpath, float _playerHeight, float _playerWidth, int _speed, Rectangle _position);
    void drawPlayer() const;


    virtual ~Player() {}
    virtual void handleInput(Input input);
    virtual void update();
    // set state depending on input
    // void SetState(PlayerState state);

    AnimationHandler animationHandler;
    float height;
    float width;
    int speed;
    Rectangle position;

private:
    Texture texture{};
    PlayerState* state_;
};

class IdleState : public PlayerState
{
public:
    void handleInput(Player& player, Input input) override;
    void update(Player& player) override;
};
