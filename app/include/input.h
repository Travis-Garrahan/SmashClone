#ifndef SMASHCLONE_INPUT_H
#define SMASHCLONE_INPUT_H



#endif //SMASHCLONE_INPUT_H
#include <raylib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>

typedef struct InputState
{
    // face buttons
    bool button_A_pressed;
    bool button_B_pressed;
    bool button_X_pressed;
    bool button_Y_pressed;

    // D-pad buttons
    bool button_dPadLeft_pressed;
    bool button_dPadRight_pressed;
    bool button_dPadDown_pressed;
    bool button_dPadUp_pressed;

    // bumpers
    bool button_LB_pressed;
    bool button_RB_pressed;

    // sticks & axes
    float left_trigger;
    float right_trigger;

    float left_joystick_x;
    float left_joystick_y;

    float right_joystick_x;
    float right_joystick_y;


}InputState;

SDL_GameController* InitController();
void PollInput(InputState* input, SDL_GameController* controller);
