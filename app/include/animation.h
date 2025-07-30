//
// Created by travis on 6/21/25.
//
#pragma once

#include "raylib.h"
#include <vector>

enum Direction
{
    FORWARD,
    BACKWARD,
};

enum AnimationType
{
    REPEATING,
    ONESHOT,
};


class Animation
{
public:
    Animation(Texture2D _spriteSheet, unsigned int _framesPerSecond, unsigned int _numFrames, float frameHeight, float frameWidth);
    void UpdateAnimation();
    void DrawAnimation() const;

private:
    Texture2D spriteSheet{};
    Rectangle frameRec{}; // frameRec will get dimensions from texture.x, texture.y, etc
    Vector2 position{};

    unsigned int framesPerSecond;
    unsigned int numFrames;
    unsigned int currentFrame;

    Vector2 origin{};
    float rotation;
    Color tint{};
};


