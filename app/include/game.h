//
// Created by travis on 8/22/25.
//

#ifndef GAME_H
#define GAME_H
#include "player.h"

enum class GameState
{
    Init,
    Running,
    Paused,
    Exiting,
};

class Game {
public:
    static void init();
    static void update(Player& player);
    static void draw(Player& player);
    static void drawPauseMenu();
    static void exit();

    static bool shouldQuit;
    static bool shouldPause;
};



#endif //GAME_H
