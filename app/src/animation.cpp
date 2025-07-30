#include "animation.h"

static int framesCounter = 0;

Animation::Animation(Texture2D _spriteSheet, unsigned int _framesPerSecond, unsigned int _numFrames, float frameHeight, float frameWidth)
{
    spriteSheet = _spriteSheet;

    frameRec = (Rectangle){0, 0, frameHeight, frameWidth};
    framesPerSecond = _framesPerSecond;
    numFrames = _numFrames;

    currentFrame = 0;
    origin = {0,0};
    rotation = 0.0f;
    tint = WHITE;

    position = {100, 100};
}

void Animation::UpdateAnimation()
{
    framesCounter++;
    if(framesCounter >= (60/framesPerSecond))
    {
        framesCounter = 0;
        currentFrame++;

        if(currentFrame >= numFrames) currentFrame = 0;

        frameRec.x = (float)currentFrame*(float)frameRec.width;
    }
}

void Animation::DrawAnimation() const
{
    //TODO: use DrawTexturePro() instead
    DrawTextureRec(spriteSheet, frameRec, position, tint);
}

