//
// Created by Travis Garrahan on 6/27/25.
//

#include "input.h"

SDL_GameController* InitController()
{
    // Controller setup
    // --------------------------------------------------------------------------------------------
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0) {
        printf("SDL2 could not be initialized: ");
        printf("%s\n", SDL_GetError());
    } else {
        printf("SDL2 video init + joystick init success\n");
    }

    // Database of controller mappings, if mappings are messed up, its probably this file
    SDL_GameControllerAddMappingsFromFile(R"(controller_mappings/gamecontrollerdb.txt)");
    SDL_GameController *controller = nullptr;

    if (SDL_IsGameController(0))
    {
        controller = SDL_GameControllerOpen(0);
        printf("Opened as GameController %s\n", SDL_GameControllerName(controller));
    }

    return controller;
    // --------------------------------------------------------------------------------------------
    // End controller setup
}

void PollInput(InputState* input, SDL_GameController* controller)
{
    // Set axis deadzones
    const float leftStickDeadzoneX = 0.1f;
    const float leftStickDeadzoneY = 0.1f;
    const float rightStickDeadzoneX = 0.1f;
    const float rightStickDeadzoneY = 0.1f;
    const float leftTriggerDeadzone = -0.9f;
    const float rightTriggerDeadzone = -0.9f;

    input->button_A_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
    input->button_B_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
    input->button_X_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
    input->button_Y_pressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);

    input->left_joystick_x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    input->left_joystick_y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
    input->right_joystick_x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
    input->right_joystick_y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
    input->left_trigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    input->right_trigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

    // Calculate deadzones
//    if(input->left_joystick_x > -leftStickDeadzoneX && input->left_joystick_x < leftStickDeadzoneX)
//        input->left_joystick_x = 0.0f;
//    if(input->left_joystick_y > -leftStickDeadzoneY && input->left_joystick_y < leftStickDeadzoneY)
//        input->left_joystick_y = 0.0f;
//
//    if(input->right_joystick_x > -rightStickDeadzoneX && input->right_joystick_x < rightStickDeadzoneX)
//        input->right_joystick_x = 0.0f;
//    if(input->right_joystick_y > -rightStickDeadzoneY && input->right_joystick_y < rightStickDeadzoneY)
//        input->right_joystick_y = 0.0f;
//
//    if(input->left_trigger < leftTriggerDeadzone)
//        input->left_trigger = 0.0f;
//    if(input->right_trigger < rightTriggerDeadzone)
//        input->right_trigger = 0.0f;
}