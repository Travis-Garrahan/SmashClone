//
// Created by travis on 8/15/25.
//
#pragma once
#include "input.h"


#ifndef STATES_H
#define STATES_H

#endif //STATES_H
class Player;


class PlayerState
{
public:
    virtual ~PlayerState() = default;
    virtual void handleInput(Player& player, Input input) {}
    virtual void update(Player& player, Input input) {}
};

class IdleState : public PlayerState
{
public:
    void handleInput(Player& player, Input input) override;
    void update(Player& player, Input input) override;
};


class RunningState : public PlayerState
{
public:
    void handleInput(Player& player, Input input) override;
    void update(Player& player, Input input) override;
};

class JumpingState : public PlayerState
{
    bool appliedImpulse = false;

public:
    void handleInput(Player& player, Input input) override;
    void update(Player& player, Input input) override;
};