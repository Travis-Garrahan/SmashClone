//
// Created by travis on 6/21/25.
//
#pragma once

#include "raylib.h"
#include <vector>

struct Frame
{
    Rectangle sourceRect;
    float duration = 1.0f;
};

struct Animation
{
    std::vector<Frame> frames;
    float timer = 0.0f;
    size_t currentFrame = 0;

    explicit Animation(const std::vector<Frame>& _frames);
    void update();
    [[nodiscard]] Frame getCurrentFrame() const;
};


