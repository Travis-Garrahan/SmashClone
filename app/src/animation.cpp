#include "animation.h"
#include <fstream>
#include <iostream>
#include <vector>


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

    throw std::runtime_error("Animation name '" + static_cast<std::string>(name) + "' not found");
}


AnimationHandler::AnimationHandler(const char* filePath)
{
    // AnimationHandler will set whatever animation is marked "default"
    // as the current animation when instantiated.

    // Load file
    std::ifstream file(filePath);
    if (!file.is_open()){throw std::runtime_error("Animation loading error");}
    nlohmann::json json;
    file >> json;

    int defaultIndex = -1; // sentinel value

    const auto& charData = json["redman"];
    const auto& animArray = charData["animations"];

    animations.reserve(animArray.size());
    for (const auto& animData : animArray)
    {
        animations.emplace_back(
            Animation
            {
                animData["name"].get<std::string>(),                  // name
                animData["frames_per_second"].get<unsigned int>(),    // framesPerSecond
                animData["num_frames"].get<unsigned int>(),           // numFrames
                {                                     // frameRecStart
                    animData["x"].get<float>(),
                    animData["y"].get<float>(),
                },
                animData["frame_width"].get<unsigned int>(),          // frameWidth
                animData["frame_height"].get<unsigned int>(),         // frameHeight
                animData.value("default", false),      // isDefault
                0                                                     // currentFrame
            }
        );

        if (animData.value("default", false))
        {
            defaultIndex = static_cast<int>(animations.size()) - 1;
        }
    }
    // Fallback to first animation if no default is specified
    if (defaultIndex == -1 && !animations.empty())
    {
        defaultIndex = 0;
        TraceLog(LOG_WARNING, "No default animation specified");
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

    Animation& anim = animations[currentAnimationIndex];

    frameTime += GetFrameTime();
    float frameDuration = 1.0f / static_cast<float>(animations[currentAnimationIndex].framesPerSecond);

    while (frameTime >= frameDuration)
    {
        frameTime -= frameDuration;
        anim.currentFrame = (anim.currentFrame + 1) % anim.numFrames;
    }
}

void AnimationHandler::drawAnimation(const Texture2D &spriteSheet, const Rectangle dest) const
{
    DrawTexturePro(spriteSheet,
        animations[currentAnimationIndex].getFrameRec(),
        dest,
        {0,0},
        0.0f, WHITE);
}