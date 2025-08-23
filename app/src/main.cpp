#include "raylib.h"
#include <iostream>
#include <player.h>
#include "imgui.h"
#include "rlImGui.h"
#include "game.h"

int main() {
    Game::init();

    Player player(R"(assets/attributes/player_animation_data.json)",
        512.0f, 512.0f, 200,
        (Rectangle){200, 200, 256.0f, 256.0f});

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Game::update(player);
        Game::draw(player);
    }
    Game::exit();

    return 0;
}