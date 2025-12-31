#include "raylib.h"
#include <iostream>
#include <player.h>
#include "imgui.h"
#include "rlImGui.h"
#include "game.h"

int main() {
    Game::init();

    Rectangle startingPos = { 200, 200, 256.0f, 256.0f };

    Player player(R"(assets/attributes/player_animation_data.json)",
        512.0f, 512.0f, 200,
        startingPos);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Game::update(player);
        Game::draw(player);
    }

    return 0;
}