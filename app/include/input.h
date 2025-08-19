#ifndef SMASHCLONE_INPUT_H
#define SMASHCLONE_INPUT_H

#endif //SMASHCLONE_INPUT_H
#pragma once
#include "raylib.h"

struct Input
{
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool attack = false;
    bool faceLeft = false;
    bool faceRight = false;

    [[nodiscard]] bool isMoving() const {return moveLeft || moveRight;}
};

inline Input pollInput()
{
    Input input;
    input.moveLeft = IsKeyDown(KEY_LEFT);
    input.moveRight = IsKeyDown(KEY_RIGHT);
    input.faceLeft = IsKeyPressed(KEY_LEFT);
    input.faceRight = IsKeyPressed(KEY_RIGHT);
    return input;
}