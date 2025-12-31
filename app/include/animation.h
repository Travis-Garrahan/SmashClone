//
// Created by travis on 6/21/25.
//
#pragma once
#include <raylib.h>
#include <nlohmann/json.hpp>

enum class AnimationType
{
    ONESHOT,
    LOOP
};

struct Animation
{
    std::string name;                 // "name" from JSON
    unsigned int framesPerSecond{1};  // "frames_per_second"
    unsigned int numFrames{1};        // "num_frames"
    Vector2 frameRecStart{};          // "x" and "y" in the atlas
    unsigned int frameWidth{};        // "frame_width"
    unsigned int frameHeight{};       // "frame_height"
    bool isDefault{false};            // "default" in JSON
    unsigned int currentFrame{0};     // internal state, starts at 0

    AnimationType type = AnimationType::LOOP;
    bool finished = false;            // for ONESHOT animations

    [[nodiscard]] Rectangle getFrameRec() const
    {
        return Rectangle
        {
            frameRecStart.x + static_cast<float>(currentFrame) * static_cast<float>(frameWidth),
            frameRecStart.y,
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        };
    }

};


class AnimationHandler
{
public:
    explicit AnimationHandler(const char* filePath);
    Texture2D atlas{};
    Animation* currentAnimation{};
    float frameTime{};

    void updateAnimation();
    void setCurrentAnimation(std::string_view name);
    bool isAnimationFinished() const;

private:
    std::unordered_map<std::string, Animation> animationMap;
    int currentAnimationIndex{};

};