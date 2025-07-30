#include <animation.h>
#include "raylib.h"
#include <input.h>
#include <iostream>
#include <player.h>
#include "imgui.h"
#include "rlImGui.h"

int main() {
    // Initialization
    //---------------------------------------------------------------------------------------------
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    // Imgui Window setup, flags will make window transparent with no title
    // --------------------------------------------------------------------------------------------
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar        // No title bar
            | ImGuiWindowFlags_NoResize          // Disable resizing
            | ImGuiWindowFlags_NoMove            // Disable moving
            | ImGuiWindowFlags_NoScrollbar       // No scrollbars
            | ImGuiWindowFlags_NoCollapse        // Disable collapsing
            | ImGuiWindowFlags_NoSavedSettings   // Don’t save settings (position, size, etc.)
            | ImGuiWindowFlags_NoFocusOnAppearing // Don’t steal focus when appearing
            | ImGuiWindowFlags_NoNav;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // --------------------------------------------------------------------------------------------
    // End Imgui setup

    // Player Setup
    // --------------------------------------------------------------------------------------------
    // TODO: Implement JSON player config files
    float playerHeight = 64;
    float playerWidth = 64;
    int speed = 5;
    const auto player = Player(R"(assets/player_run.png)", playerHeight, playerWidth, speed);
    std::cout << "Texture ID:" << player.GetTexture().id << std::endl;

    //
    int animationFPS = 12;
    int numFrames = 5;
    Animation animation(player.GetTexture(), animationFPS, numFrames, player.height, player.width);

    // Main game loop
    //---------------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------------------------------------------
        animation.UpdateAnimation();
        //-----------------------------------------------------------------------------------------
        // End update

        // Draw
        //-----------------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        rlImGuiBegin();
        ImGui::Render();
        // draw here...
        animation.DrawAnimation();

        rlImGuiEnd();
        EndDrawing();
        //-----------------------------------------------------------------------------------------
        // End draw
    }

    // De-Initialization
    //---------------------------------------------------------------------------------------------
    rlImGuiShutdown();
    CloseWindow();        // Close window and OpenGL context

    //---------------------------------------------------------------------------------------------
    // End De-Initialization

    return 0;
}