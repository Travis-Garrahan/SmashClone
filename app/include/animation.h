//
// Created by travis on 6/21/25.
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include <raylib.h>

#endif //ANIMATION_H

typedef struct Animation
{
    Texture2D atlas;
    int fps;

    Rectangle* frames;
    int numFrames;
} Animation;

void DrawAnimation(Animation animation, Rectangle dest, Vector2 origin, float rotation, Color tint);
Animation LoadAnimation(const Texture2D& atlas, int fps, int numFrames, float frameWidth, float frameHeight);
void DisposeAnimation(Animation animation);