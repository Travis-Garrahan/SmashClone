#include <iostream>

#include "animation.h"
#include "raylib.h"


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    // Window init
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    Texture2D idle = LoadTexture(R"(assets/sprites/Wizardgooseassets/Idle (64x64)-sheet.png)");
    Animation animation = LoadAnimation(idle, 11, 11, 64, 64);

    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing();

        DrawAnimation(animation, (Rectangle){0, 0, 128, 128}, (Vector2){0,0}, 0.0f, WHITE);

        ClearBackground(RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    DisposeAnimation(animation);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}