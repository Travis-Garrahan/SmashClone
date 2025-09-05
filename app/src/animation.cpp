#include "animation.h"
#include <fstream>
#include <iostream>

void AnimationHandler::setCurrentAnimation(const std::string_view name)
{
    auto it = animationMap.find(std::string(name));

    if (it != animationMap.end())
    {
        currentAnimation = &it->second;
    }
    else
    {
        throw std::runtime_error("Animation name '" + static_cast<std::string>(name) + "' not found");
    }

    currentAnimation->currentFrame = 0;
    currentAnimation->finished = false; // important for oneshot animations
    frameTime = 0.0f;
}

AnimationHandler::AnimationHandler(const char* filePath)
{
    // AnimationHandler will set whatever animation is marked "default"
    // when instantiated.

    // Load file
    std::ifstream file(filePath);
    if (!file.is_open()){throw std::runtime_error("Animation loading error");}
    nlohmann::json json;
    file >> json;


    for (const auto& animData : json["redman"]["animations"])
    {
        std::string typeStr = animData.value("type", "loop");
        AnimationType type = (typeStr == "oneshot") ? AnimationType::ONESHOT : AnimationType::LOOP;


            Animation anim{
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
                0,                                                     // currentFrame
                type
            };
        animationMap[anim.name] = anim;

        if (anim.isDefault && !currentAnimation)
            currentAnimation = &animationMap[anim.name];
    }
}

void AnimationHandler::updateAnimation()
{
    // null check
    if (!currentAnimation || currentAnimation->framesPerSecond == 0)
    {
        std::cout << "currentAnimation null or FPS = 0" << std::endl;
        return;
    }

    Animation& anim = *currentAnimation;

    if (anim.type == AnimationType::ONESHOT && anim.finished)
    {
        return;
    }

    frameTime += GetFrameTime();
    float frameDuration = 1.0f / static_cast<float>(anim.framesPerSecond);

    if (frameTime >= frameDuration)
    {
        frameTime -= frameDuration;

        if (anim.type == AnimationType::LOOP)
        {
            anim.currentFrame = (anim.currentFrame + 1) % anim.numFrames;
        }
        else if (anim.type == AnimationType::ONESHOT)
        {
            if (anim.currentFrame + 1 < anim.numFrames)
            {
                anim.currentFrame++;
            }
            else
            {
                anim.finished = true;
                anim.currentFrame = anim.numFrames - 1; // stay on last frame
            }
        }
    }
}

bool AnimationHandler::isAnimationFinished() const
{
    if (!currentAnimation)
    {
        return false;
    }
    return currentAnimation->type == AnimationType::ONESHOT && currentAnimation->finished;
}

