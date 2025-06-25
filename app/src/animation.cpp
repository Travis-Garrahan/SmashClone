//
// Created by travis on 6/21/25.
//

#include "animation.h"

#include <cstdlib>
#include <cstring>

void DrawAnimation(Animation animation, Rectangle dest, Vector2 origin, float rotation, Color tint)
{
    int index = (int)(GetTime() * animation.fps) % animation.numFrames;

    Rectangle source = {animation.frames[index]};
    DrawTexturePro(animation.atlas, source, dest, origin, rotation, tint);
}

Animation LoadAnimation(const Texture2D& atlas, const int fps, const int numFrames, const float frameWidth, const float frameHeight)
{
    // instantiate animation struct with given parameters
    Animation animation = {
        .atlas = atlas,
        .fps = fps,
        .numFrames = numFrames
    };

    // allocate memory for frames to live in
    Rectangle* mem = new Rectangle[numFrames];
    animation.frames = mem;


    // populate memory with frames (assumes horizontal strip)
    for (int i = 0; i < numFrames; i++)
    {
        mem[i].x = static_cast<float>(i) * frameWidth;
        mem[i].y = 0;
        mem[i].width = frameWidth;
        mem[i].height = frameHeight;
    }

    // set dimensions of frame


    return animation;
}

void DisposeAnimation(Animation animation)
{
    delete[] animation.frames;
}

