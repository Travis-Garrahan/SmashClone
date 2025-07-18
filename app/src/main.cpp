#include <animation.h>
#include "raylib.h"
#include <input.h>
#include <iostream>
#include <player.h>
#include "imgui.h"
#include "rlImGui.h"

int gamepad = 0;

int main() {
    // Initialization
    //---------------------------------------------------------------------------------------------
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    const auto player = Player(R"(assets/player_run.png)", 100, 100);

    std::cout << "Texture ID:" << player.texture.id << std::endl;

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

    // Main game loop
    //---------------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------------------------------------------

        //-----------------------------------------------------------------------------------------
        // End update

        // Draw
        //-----------------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        rlImGuiBegin();
        ImGui::Render();
        rlImGuiEnd();

        player.DrawPlayer();

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