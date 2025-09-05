//
// Created by travis on 8/22/25.
//

#include "../include/game.h"
#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "input.h"

void Game::init()
{
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 768;
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
}

void Game::update(Player& player)
{
    Input input = pollInput();
    player.handleInput(input);
    player.update(input);
    player.animationHandler.updateAnimation();
}

void Game::draw(Player& player)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    rlImGuiBegin();

    ImGui::Render();
    player.drawPlayer();

    rlImGuiEnd();
    EndDrawing();
}

void Game::exit()
{
    rlImGuiShutdown();
    CloseWindow();        // Close window and OpenGL context
}
