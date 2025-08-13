#include "animation.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

Animation::Animation(std::string _name,
    const unsigned int _framesPerSecond,
    const unsigned int _numFrames,
    const float frameHeight,
    const float frameWidth)
: name(std::move(_name)),
  framesPerSecond(_framesPerSecond ? _framesPerSecond : 1), // Ensure never 0
  numFrames(_numFrames ? _numFrames : 1),   // Ensure never 0
  frameRecSize{0, 0, frameWidth, frameHeight}, // Fixed width/height order
  currentFrame(0)
{
    if (_framesPerSecond == 0 || numFrames == 0)
    {
        TraceLog(LOG_WARNING, "Animation %s has invalid params (FPS: %u, Frames: %u)",
        name.c_str(), _framesPerSecond, numFrames);
    }
}

void AnimationHandler::setCurrentAnimation(std::string_view name)
{
    for (size_t i = 0; i < animations.size(); i++)
    {
        if (animations[i].name == name)
        {
            currentAnimationIndex = static_cast<int>(i);
            return;
        }
    }

    //throw std::runtime_error("Animation name '" + name + "' not found");
}

Animation AnimationHandler::getCurrentAnimation() const
{
    return animations[currentAnimationIndex];
}

AnimationHandler::AnimationHandler(const char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()){throw std::runtime_error("Animation loading error");}
    nlohmann::json json;
    file >> json;

    int defaultIndex = -1; // sentinel value

    animations.reserve(json["animations"].size());
    for (size_t i = 0; i < json["animations"].size(); i++)
    {
        const auto& animData = json["animations"][i];

        animations.emplace_back(
            animData["name"],
            animData["frames_per_second"],
            animData["num_frames"],
            animData["frame_height"],
            animData["frame_width"]
        );

        if (animData.value("default", false))
        {
            defaultIndex = static_cast<int>(i);
        }

        // Fallback to first animation if no default is specified
        if (defaultIndex == -1 && !animations.empty())
        {
            defaultIndex = 0;
        }
    }

    currentAnimationIndex = defaultIndex;
}

void AnimationHandler::updateAnimation()
{
    // null check
    if (animations[currentAnimationIndex].framesPerSecond == 0)
    {
        std::cout << "currentAnimation null" << std::endl;
        return;
    }

    frameTime += GetFrameTime();
    float frameDuration = 1.0f / animations[currentAnimationIndex].framesPerSecond;

    if (frameTime >= frameDuration)
    {
        frameTime = 0.0f;
        animations[currentAnimationIndex].currentFrame++;

        // loop animation
        if (animations[currentAnimationIndex].currentFrame > animations[currentAnimationIndex].numFrames)
        {
            animations[currentAnimationIndex].currentFrame = 0;
        }

        // update source rectangle
        animations[currentAnimationIndex].frameRecSize.x =
            static_cast<float>(animations[currentAnimationIndex].currentFrame) * animations[currentAnimationIndex].frameRecSize.width;
    }
}

void AnimationHandler::drawAnimation(const Texture2D &spriteSheet, const Rectangle dest) const
{
    DrawTexturePro(spriteSheet, animations[currentAnimationIndex].frameRecSize, dest, {0,0}, 0.0f, WHITE);
}