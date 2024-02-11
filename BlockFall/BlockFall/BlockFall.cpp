#include "BlockFall.h"

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

void BlockFall::read_blocks(const string &input_file) {
    ifstream file(input_file);

    string line;
    Block* block_tail = new Block();
    vector<bool> row;

    bool empty_flag = false;

    while (std::getline(file, line)) {
        if (!(line.empty() || (line.size() == 1 && (line[0] == '\n' || line[0] == '\r')))) {
            for (char c : line) {
                if (c == '0' || c == '1') {
                    row.push_back(c == '1');
                }
            }
            block_tail->shape.push_back(row);
            row.clear();
            empty_flag = false;
        } else {
            if (empty_flag) {
                continue;
            }
            empty_flag = true;

            block_tail->applyRotations();
            if (initial_block == nullptr) {
                initial_block = block_tail;
            }
            block_tail->next_block = new Block();
            block_tail = block_tail->next_block;
            continue;
        }
    }
    
    power_up = block_tail->shape;

    Block* previous_block = initial_block;
    while (previous_block->next_block->next_block != nullptr) {
        previous_block = previous_block->next_block;
    }

    delete block_tail;
    if (previous_block) {
        previous_block->next_block = nullptr;
    }

    active_rotation = initial_block;

    file.close();
}

void BlockFall::initialize_grid(const string &input_file) {
    std::ifstream file(input_file);

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int value;
        while (iss >> value) {
            row.push_back(value);
        }
        grid.push_back(row);
    }

    rows = grid.size();
    cols = grid[0].size();

    file.close();
}


BlockFall::~BlockFall() {
    Block* current = initial_block;
    while (current) {
        Block* temp = current;
        current = current->next_block;
        
        delete temp->right_rotation->right_rotation->right_rotation;
        temp->right_rotation->right_rotation->right_rotation = nullptr;

        delete temp->right_rotation->right_rotation;
        temp->right_rotation->right_rotation = nullptr;

        delete temp->right_rotation;
        temp->right_rotation = nullptr;

        delete temp;
        temp = nullptr;
    }
}
