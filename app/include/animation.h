//
// Created by travis on 6/21/25.
//
#pragma once

#include <vector>
#include <raylib.h>
#include <nlohmann/json.hpp>

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


struct Animation
{
    Animation(std::string _name, unsigned int _framesPerSecond, unsigned int _numFrames, float frameHeight, float frameWidth);
    std::string name;
    unsigned int currentFrame;
    Rectangle frameRecSize{};
    unsigned int framesPerSecond;
    unsigned int numFrames;
    bool isDefault;
};

class AnimationHandler
{
public:
    explicit AnimationHandler(const char* filePath);
    void updateAnimation();
    void setCurrentAnimation(std::string_view name);
    [[nodiscard]] Animation getCurrentAnimation() const;
    void drawAnimation(const Texture2D &spriteSheet, Rectangle dest) const;

private:
    std::vector<Animation> animations;
    int currentAnimationIndex = 0;
    float frameTime = 0.0f;
};