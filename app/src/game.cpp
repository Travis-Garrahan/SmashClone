//
// Created by travis on 8/22/25.
//

#include "../include/game.h"
#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "input.h"

bool Game::shouldPause = false;
bool Game::shouldQuit = false;

void Game::init()
{
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    // disable ESC closing app
    SetExitKey(0);

}

void Game::update(Player& player)
{
    Input input = pollInput();
    player.handleInput(input);

    if (IsKeyPressed(KEY_ESCAPE))
    {
        shouldPause = !shouldPause;
    }

    if (!shouldPause)
    {
        player.update(input);
        player.animationHandler.updateAnimation();
    }

    if (shouldQuit)
    {
        exit();
    }
}

void Game::draw(Player& player)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    player.drawPlayer();

    if (shouldPause)
    {
        drawPauseMenu();
    }

    EndDrawing();
}

void Game::drawPauseMenu()
{
    rlImGuiBegin();

    ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::Begin(
        "Pause Menu",
        nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove
    );

    ImGui::Text("Paused");
    ImGui::Spacing();
    
    if (ImGui::Button("Resume"))
    {
        shouldPause = false;
    }

    if (ImGui::Button("Quit"))
    {
        shouldQuit = true;
    }

    ImGui::End();

    rlImGuiEnd();
}

void Game::exit()
{
    rlImGuiShutdown();
    CloseWindow();        // Close window and OpenGL context
}
