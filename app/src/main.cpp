#include <animation.h>
#include "raylib.h"
#include <input.h>
#include "imgui.h"
#include "rlImGui.h"

int main() {
    // Initialization
    //---------------------------------------------------------------------------------------------

    // Window init
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    // Imgui Window setup, flags will make window transparent with no title
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

    // Controller setup
    // --------------------------------------------------------------------------------------------
    SDL_GameController* controller = InitController();

    float lx, ly;
    float rx, ry;
    InputState inputState;

    // --------------------------------------------------------------------------------------------
    // End controller setup

    // Main game loop
    //---------------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------------------------------------------
        SDL_PumpEvents();
        PollInput(&inputState, controller);

        // Left Joystick
        lx = inputState.left_joystick_x;
        ly = inputState.left_joystick_y;

        // Right joystick
        rx = inputState.right_joystick_x;
        ry = inputState.right_joystick_y;
        //-----------------------------------------------------------------------------------------
        // End update

        // Draw
        //-----------------------------------------------------------------------------------------
        BeginDrawing();
        rlImGuiBegin();


        DrawCircle((int)(lx * 0.01), (int)(ly * -0.01), 50, RED);
        DrawCircle((int)(rx * 0.01), (int)(ry * -0.01), 25, GREEN);


        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin("##NoDecoration", nullptr, window_flags);
        ImGui::Button("Button");
        ImGui::End();

        if(inputState.button_A_pressed)
        {
            DrawText(TextFormat("A button pressed"), 50, 50, 50, BLACK);
        }

        ClearBackground(RAYWHITE);

        ImGui::Render();

        rlImGuiEnd();
        EndDrawing();
        //-----------------------------------------------------------------------------------------
        // End draw
    }

    // De-Initialization
    //---------------------------------------------------------------------------------------------
    SDL_GameControllerClose(controller);
    rlImGuiShutdown();


    CloseWindow();        // Close window and OpenGL context

    //---------------------------------------------------------------------------------------------

    return 0;
}