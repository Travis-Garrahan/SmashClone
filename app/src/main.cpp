#include <animation.h>
#include <raylib.h>
#include <input.h>

int main() {
    // Initialization
    //---------------------------------------------------------------------------------------------

    // Window init
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    // Controller setup
    // --------------------------------------------------------------------------------------------
    SDL_GameController* controller = InitController();
    SDL_GameControllerAddMapping("0300aa4e5e040000120b000009056800,Xbox Series X Controller,a:b0,b:b1,back:b8,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,leftshoulder:b4,leftstick:b6,lefttrigger:a2,leftx:a0,lefty:a1,misc1:b10,rightshoulder:b5,rightstick:b7,righttrigger:a5,rightx:a3,righty:a4,start:b9,x:b2,y:b3");

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

        SDL_Joystick* joy = SDL_GameControllerGetJoystick(controller);

        for (int i = 0; i < SDL_JoystickNumAxes(joy); i++) {
            Sint16 val = SDL_JoystickGetAxis(joy, i);
            if (abs(val) > 5000) {
                printf("AXIS %d = %d\n", i, val);
            }
        }

        for (int i = 0; i < SDL_JoystickNumButtons(joy); i++) {
            if (SDL_JoystickGetButton(joy, i)) {
                printf("BUTTON %d pressed\n", i);
            }
        }



        // Left Joystick
        lx = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
        ly = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
        // Right joystick
        rx = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
        ry = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
        PollInput(&inputState, controller);
        //-----------------------------------------------------------------------------------------
        // End update

        // Draw
        //-----------------------------------------------------------------------------------------
        BeginDrawing();

        DrawCircle(lx * 0.01, ly * -0.01, 50, RED);
        DrawCircle(rx * 0.01, ry * -0.01, 25, GREEN);

        if(inputState.button_A_pressed)
        {
            DrawText(TextFormat("A button pressed"), 50, 50, 50, BLACK);
        }

        ClearBackground(RAYWHITE);
        EndDrawing();
        //-----------------------------------------------------------------------------------------
        // End draw
    }

    // De-Initialization
    //---------------------------------------------------------------------------------------------
    SDL_GameControllerClose(controller);
    CloseWindow();        // Close window and OpenGL context

    //---------------------------------------------------------------------------------------------

    return 0;
}