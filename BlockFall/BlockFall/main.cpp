#include "BlockFall.h"
#include "GameController.h"
#include <iostream>

int main(int argc, char **argv) {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    // Create a BlockFall instance
    string gravity_mode("GRAVITY_OFF");
    BlockFall game("grid.dat", "blocks.dat", (gravity_mode == "GRAVITY_ON"), "leaderboard.txt", name);

    // Create a GameController instance
    GameController controller;

    // Play
    controller.play(game);
    system("pause");

    return 0;
}