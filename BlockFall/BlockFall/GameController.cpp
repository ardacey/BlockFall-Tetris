#include "GameController.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <windows.h>

bool isPowerUpActivated(const std::vector<std::vector<int>>& grid, const std::vector<std::vector<bool>>& shape, int startX, int startY) {
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] != grid[startX + i][startY + j]) {
                return false;
            }
        }
    }
    return true;
}

void clearScreen(){	
    COORD topLeft = {0, 0};
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(consoleHandle, &screen);
    FillConsoleOutputCharacter(consoleHandle, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(consoleHandle, topLeft);
}

bool GameController::play(BlockFall& game){

    int rightCount = 0;
    bool couldntFit = false;
    bool noMoreBlocks = false;
    char key;
    Block* current_block = game.initial_block;

    int main_standby1_flag = 3;
    int main_standby2_flag = 0;
    int main_clear_flag = 0;
    int clear_count = 0;
    bool clear_flag = false;
    

    std::string line;

    for (int i = 0; i < current_block->shape.size(); i++){
        for (int j = 0; j < current_block->shape[0].size(); j++){
            game.grid[i][j] = current_block->shape[i][j];
        }
    }
    std::cout << "Score: " << game.current_score << "\n";
    std::cout << "High Score: " << game.leaderboard.head_leaderboard_entry->score << "\n";
    for (int i = 0; i < game.grid.size(); i++) {
        for (int j = 0; j < game.grid[0].size(); j++) {
            if(game.grid[i][j]) std::cout << occupiedCellChar;
            else std::cout << unoccupiedCellChar;
        }
        std::cout << "\n";
    }

    while (true) {
        if (couldntFit || noMoreBlocks) break;
        if (_kbhit()) {
            key = _getch();
            switch (key) {
                case 'e': {
                    bool rotateRightErrorFlag = false;
                    for (int i = 0; i < game.active_rotation->shape.size(); i++){
                        for (int j = 0; j < game.active_rotation->shape[0].size(); j++){
                            if (j + rightCount < game.cols) game.grid[i][j+rightCount] = 0;
                        }
                    }
                    for (int i = 0; i < game.active_rotation->right_rotation->shape.size(); i++) {
                        for (int j = 0; j < game.active_rotation->right_rotation->shape[0].size(); j++){
                            if (game.active_rotation->right_rotation->shape[i][j] == 1 && 
                            (j+game.active_rotation->right_rotation->shape[0].size()-1 < game.cols && game.grid[i][j+game.active_rotation->right_rotation->shape[0].size()-1]) == 1){
                                rotateRightErrorFlag = true;
                            }
                        }
                    }
                    if (game.active_rotation->right_rotation->shape[0].size() + rightCount > game.cols) rotateRightErrorFlag = true;
                    if(!rotateRightErrorFlag) game.active_rotation = game.active_rotation->right_rotation;
                    for (int i = 0; i < game.active_rotation->shape.size(); i++){
                        for (int j = 0; j < game.active_rotation->shape[0].size(); j++){
                            if (j + rightCount < game.cols) game.grid[i][j+rightCount] = game.active_rotation->shape[i][j];
                        }
                    }
                    break;
                }
                case 'q': {
                    bool rotateLeftErrorFlag = false;
                    for (int i = 0; i < game.active_rotation->shape.size(); i++){
                        for (int j = 0; j < game.active_rotation->shape[0].size(); j++){
                            if (j + rightCount < game.cols) game.grid[i][j+rightCount] = 0;
                        }
                    }
                    for (int i = 0; i < game.active_rotation->left_rotation->shape.size(); i++) {
                        for (int j = 0; j < game.active_rotation->left_rotation->shape[0].size(); j++){
                            if (game.active_rotation->left_rotation->shape[i][j] == 1 && 
                            (j+rightCount < game.cols && game.grid[i][j+rightCount]) == 1){
                                rotateLeftErrorFlag = true;
                            }
                        }
                    }
                    if (game.active_rotation->left_rotation->shape[0].size() + rightCount > game.cols) rotateLeftErrorFlag = true;
                    if(!rotateLeftErrorFlag) game.active_rotation = game.active_rotation->left_rotation;
                    for (int i = 0; i < game.active_rotation->shape.size(); i++){
                        for (int j = 0; j < game.active_rotation->shape[0].size(); j++){
                            if (j + rightCount < game.cols) game.grid[i][j+rightCount] = game.active_rotation->shape[i][j];
                        }
                    }
                    break;
                }
                case 'd': {
            bool moveRightErrorFlag = false;
                    for (int i = 0; i < game.active_rotation->shape.size(); i++){
                        if((game.active_rotation->shape[0].size()+rightCount < game.cols && game.grid[i][game.active_rotation->shape[0].size()+rightCount] == 1) && 
                        game.active_rotation->shape[i][game.active_rotation->shape[0].size()-1] == 1) moveRightErrorFlag = true;
                    }
                    if((rightCount+game.active_rotation->shape[0].size()) == game.cols) moveRightErrorFlag = true;
                    if(!moveRightErrorFlag){
                        for (int i = 0; i < game.active_rotation->shape.size(); i++){
                            for (int j = 0; j < game.active_rotation->shape[0].size(); j++){
                                game.grid[i][j+rightCount+1] = game.active_rotation->shape[i][j];
                            }
                            game.grid[i][rightCount] = 0;
                        }
                        rightCount++;
                    }
                    break;
                }
                case 'a': {
                    bool moveLeftErrorFlag = false;
                    for (int i = 0; i < game.active_rotation->shape.size(); i++){
                        if((rightCount > 0 && game.grid[i][rightCount-1] == 1) && game.active_rotation->shape[i][0] == 1) moveLeftErrorFlag = true;
                    }
                    if(rightCount == 0) moveLeftErrorFlag = true;
                    if(!moveLeftErrorFlag){
                        for (int i = 0; i < game.active_rotation->shape.size(); i++){
                            for (int j = 0; j < game.active_rotation->shape[0].size(); j++){
                                game.grid[i][j+rightCount-1] = game.active_rotation->shape[i][j];
                            }
                            game.grid[i][rightCount+game.active_rotation->shape[0].size()-1] = 0;
                        }
                        rightCount--;
                    }
                    break;
                }
                case 's': {
                    bool dropping = true;
                    int dropDistance = 0;
                    int occupiedCells = 0;
                    for (int i = 0; i < game.active_rotation->shape.size(); i++){
                        for (int j = 0; j < game.active_rotation->shape[0].size(); j++){
                            if(game.active_rotation->shape[i][j]) occupiedCells++;
                        }
                    }
                    while (dropping) {
                        bool canMoveDown = true;
                        for (int col = 0; col < game.active_rotation->shape[0].size(); col++) {
                            int curr_row = 0;
                            for (int row = 0; row < game.active_rotation->shape.size(); row++) {
                                if (game.active_rotation->shape[row][col] == 1) curr_row = row;
                            }
                            if (dropDistance == game.rows-game.active_rotation->shape.size() || game.grid[curr_row+dropDistance+1][col+rightCount] == 1){
                                canMoveDown = false;
                                break;
                            }
                        }

                        if (canMoveDown) {
                            for (int i = game.active_rotation->shape.size() - 1; i >= 0; i--) {
                                for (int j = 0; j < game.active_rotation->shape[0].size(); j++) {
                                    if (game.grid[i + 1 + dropDistance][j + rightCount] == 1 && game.active_rotation->shape[i][j] == 0) continue;
                                    game.grid[i + 1 + dropDistance][j + rightCount] = game.active_rotation->shape[i][j];
                                    game.grid[i + dropDistance][j + rightCount] = 0;
                                }
                            }
                            dropDistance++;
                        } else {
                            if (game.gravity_mode_on) {
                                for (int i = game.active_rotation->shape.size() - 1; i >= 0 ; i--){
                                    for (int j = 0; j < game.active_rotation->shape[0].size(); j++) {
                                        int gravityDistance = 0;
                                        while (dropDistance + gravityDistance + i + 1 != game.rows && 
                                        game.grid[i + dropDistance + gravityDistance + 1][j + rightCount] != 1) {
                                            game.grid[i + dropDistance + gravityDistance + 1][j + rightCount] = game.grid[i + dropDistance + gravityDistance][j + rightCount];
                                            game.grid[i + dropDistance + gravityDistance][j + rightCount] = 0;
                                            gravityDistance++;
                                        }
                                    }
                                }
                            }
                            dropping = false;
                        }
                    }

                    bool powerUpActivated = false;

                    for (int i = 0; i < game.rows - game.power_up.size()+1; ++i) {
                        if (powerUpActivated) break;
                        for (int j = 0; j < game.cols - game.power_up[0].size()+1; ++j) {
                            if (isPowerUpActivated(game.grid, game.power_up, i, j)) {
                                std::cout << "Before clearing:\n";
                                for (int i = 0; i < game.grid.size(); i++) {
                                    for (int j = 0; j < game.grid[0].size(); j++) {
                                        if(game.grid[i][j]) std::cout << occupiedCellChar;
                                        else std::cout << unoccupiedCellChar;
                                    }
                                    std::cout << "\n";
                                }
                                std::cout << "\n\n";
                                for (int i = 0; i < game.grid.size(); i++){
                                    for (int j = 0; j < game.grid[0].size(); j++){
                                        if (game.grid[i][j]) game.current_score++;
                                        game.grid[i][j] = 0;
                                    }
                                }
                                game.current_score += 1000;
                                powerUpActivated = true;
                                clear_flag = true;
                                break;
                            }
                        }
                    }

                    for (int row = 0; row < game.rows; row++) {
                        bool isFullRow = true;
                        for (int col = 0; col < game.cols; col++) {
                            if (game.grid[row][col] == 0) {
                                isFullRow = false;
                                break;
                            }
                        }

                        if (isFullRow) {
                            for (int col = 0; col < game.cols; col++) {
                                game.grid[row][col] = 0;
                            }
                            for (int i = row-1; i > 0; i--) {
                                for (int col = 0; col < game.cols; col++) {
                                    game.grid[i + 1][col] = game.grid[i][col];
                                }
                            }
                            game.current_score += game.cols;
                            clear_flag = true;
                        }
                    }
                    game.current_score += occupiedCells * dropDistance;
                    rightCount = 0;
                    if (current_block->next_block == nullptr) {
                        noMoreBlocks = true;
                        break;
                    }
                    current_block = current_block->next_block;
                    game.active_rotation = current_block;
                    for (int i = 0; i < current_block->shape.size(); i++){
                        for (int j = 0; j < current_block->shape[0].size(); j++){
                            if(game.grid[i][j] == 1 && current_block->shape[i][j] == 1) {
                                couldntFit = true;
                            }
                        }
                    }
                    if (couldntFit) break;
                    for (int i = 0; i < current_block->shape.size(); i++){
                        for (int j = 0; j < current_block->shape[0].size(); j++){
                            if (game.grid[i][j] == 1) continue;
                            game.grid[i][j] = current_block->shape[i][j];
                        }
                    }
                    break;
                }
                case 'w': {
                    game.gravity_mode_on = !game.gravity_mode_on;
                    if (game.gravity_mode_on) {
                        for (int i = game.rows - 1; i >= 0 ; i--){
                            for (int j = 0; j < game.cols; j++) {
                                int gravityDistance = 0;
                                while (gravityDistance + i + 1 != game.rows && game.grid[i + gravityDistance + 1][j] != 1) {
                                    if (i + gravityDistance <= game.active_rotation->shape.size() && 
                                    j <= game.active_rotation->shape[0].size() + rightCount) break;
                                    game.grid[i + gravityDistance + 1][j] = game.grid[i + gravityDistance][j];
                                    game.grid[i + gravityDistance][j] = 0;
                                    gravityDistance++;
                                }
                            }
                        }
                    }
                    for (int row = 0; row < game.rows; row++) {
                        bool isFullRow = true;
                        for (int col = 0; col < game.cols; col++) {
                            if (game.grid[row][col] == 0) {
                                isFullRow = false;
                                break;
                            }
                        }
                        if (isFullRow) {
                            for (int col = 0; col < game.cols; col++) {
                                game.grid[row][col] = 0;
                            }
                            for (int i = row-1; i > game.active_rotation->shape.size(); i--) {
                                for (int col = 0; col < game.cols; col++) {
                                    game.grid[i + 1][col] = game.grid[i][col];
                                }
                            }
                            game.current_score += game.cols;
                        }
                    }
                    break;
                }
            }

        }
        clearScreen();
        std::cout << "[A] Move Left\t[D] Move Right" << std::endl;
        std::cout << "[Q] Rotate Left\t[E] Rotate Right" << std::endl;
        std::cout << "[S] Drop\t[W] Change Gravity" << std::endl;
        std::cout << "Score: " << game.current_score << "\tGravity: ";
        if (game.gravity_mode_on) std::cout << "ON\n";
        else std::cout << "OFF\n";
        std::cout << "High Score: " << game.leaderboard.head_leaderboard_entry->score << std::endl;
        std::cout << "Next Block:\t";
        if (current_block->next_block != nullptr) {
            for (int i = 0; i < current_block->next_block->shape.size(); i++){
                if (i != 0) std::cout << "\t\t";
                for (int j = 0; j < current_block->next_block->shape[0].size(); j++){
                    if(current_block->next_block->shape[i][j]) std::cout << occupiedCellChar;
                    else std::cout << unoccupiedCellChar;
                }
                std::cout << "\n";
            }
        }
        std::cout << "\n";

        std::ifstream main_standby1("characters/main/main_standby1.dat");
        std::ifstream main_standby2("characters/main/main_standby2.dat");
        std::ifstream main_clear("characters/main/main_clear.dat");

        for (int i = 0; i < game.grid.size(); i++) {
            for (int j = 0; j < game.grid[0].size(); j++) {
                if(game.grid[i][j]) std::cout << occupiedCellChar;
                else std::cout << unoccupiedCellChar;
            }

            if (main_clear_flag > 0) {
                std::getline(main_clear, line);
            } else if (main_standby1_flag > 0) {
                std::getline(main_standby1, line);
            } else if (main_standby2_flag > 0) {
                std::getline(main_standby2, line);
            }
            std::cout << line << std::endl;
        }

        main_standby1.close();
        main_standby2.close();
        main_clear.close();

        if (main_clear_flag > 0 ) {
            main_clear_flag--;
        } else if (main_standby1_flag > 0) {
            main_standby1_flag--;
            if (main_standby1_flag == 0) {
                if (clear_count > 0) {
                    main_clear_flag = 3;
                    clear_count--;
                }
                main_standby2_flag = 3;
            }
        } else if (main_standby2_flag > 0) {
            main_standby2_flag--;
            if (main_standby2_flag == 0) {
                if (clear_count > 0) {
                    main_clear_flag = 3;
                    clear_count--;
                }
                main_standby1_flag = 3;
            }
        }
        if (clear_flag) {
            main_clear_flag = 3;
            clear_count = 3;
            clear_flag = false;
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (couldntFit){
        std::cout << "GAME OVER!\n";
        std::cout << "Next block that couldn't fit:\n";
        for (int i = 0; i < current_block->shape.size(); i++){
            for (int j = 0; j < current_block->shape[0].size(); j++){
                if(current_block->shape[i][j]) std::cout << occupiedCellChar;
                else std::cout << unoccupiedCellChar;
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    else if(noMoreBlocks){
        std::cout << "YOU WIN!\n";
        std::cout << "No more blocks.\n";
    }
    else {
        std::cout << "GAME FINISHED!\n";
        std::cout << "No more commands.\n";
        for (int i = 0; i < current_block->shape.size(); i++){
            for (int j = 0; j < current_block->shape[0].size(); j++){
                game.grid[i][j+rightCount] = 0;
            }
        }
    }

    std::cout << "Final grid and score:\n\n";
    std::cout << "Score: " << game.current_score << "\n";
    std::cout << "High Score: " << game.leaderboard.head_leaderboard_entry->score << "\n";
    for (int i = 0; i < game.grid.size(); i++) {
        for (int j = 0; j < game.grid[0].size(); j++) {
            if(game.grid[i][j]) std::cout << occupiedCellChar;
            else std::cout << unoccupiedCellChar;
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    time_t now = time(NULL);

    LeaderboardEntry* new_entry = new LeaderboardEntry(game.current_score, now, game.player_name);

    game.leaderboard.insert_new_entry(new_entry);

    game.leaderboard.write_to_file("leaderboard.txt");

    game.leaderboard.print_leaderboard();

    if (couldntFit) return false;
    return true;
}