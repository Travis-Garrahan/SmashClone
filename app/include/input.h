#ifndef SMASHCLONE_INPUT_H
#define SMASHCLONE_INPUT_H

#endif //SMASHCLONE_INPUT_H

#include "raylib.h"

struct Input
{
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool attack = false;

    void update()
    {
        moveLeft = IsKeyDown(KEY_LEFT);
        moveRight = IsKeyDown(KEY_RIGHT);
        jump = IsKeyDown(KEY_SPACE);
        attack = IsKeyDown(KEY_M);
    }

    bool isMoving() const {return moveLeft || moveRight;}
};