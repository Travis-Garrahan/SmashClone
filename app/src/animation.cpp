#include "animation.h"

Animation::Animation(const std::vector<Frame>& _frames)
{
    frames = _frames;
}

void Animation::update()
{
    if (frames.empty()) return;

    timer += GetFrameTime();
    while (timer >= frames[currentFrame].duration)
    {
        timer -= frames[currentFrame].duration;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

[[nodiscard]] Frame Animation::getCurrentFrame() const
{
    return frames[currentFrame];
}