#pragma once

#include "Game.hpp"

int main() {
    Game* game = new Game();
    game->run();
    delete game;
    return 0;
}