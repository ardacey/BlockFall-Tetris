#ifndef PA2_BLOCK_H
#define PA2_BLOCK_H

#include <vector>

using namespace std;

class Block {
public:

    vector<vector<bool>> shape; // Two-dimensional vector corresponding to the block's shape
    Block * right_rotation = nullptr; // Pointer to the block's clockwise neighbor block (its right rotation)
    Block * left_rotation = nullptr; // Pointer to the block's counter-clockwise neighbor block (its left rotation)
    Block * next_block = nullptr; // Pointer to the next block to appear in the game

    bool operator==(const Block& other) const {
        if (shape.size() != other.shape.size() || shape[0].size() != other.shape[0].size()) {
            return false;
        }
        for (int i = 0; i < shape.size(); ++i) {
            for (int j = 0; j < shape[0].size(); ++j) {
                if (shape[i][j] != other.shape[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Block& other) const {
        return !(*this == other);
    }

    void applyRotations() {
        this->right_rotation = Block::rotateRight(this);
        this->right_rotation->next_block = this->next_block;

        this->right_rotation->right_rotation = Block::rotateRight(this->right_rotation);
        this->right_rotation->right_rotation->next_block = this->next_block;

        this->right_rotation->right_rotation->right_rotation = Block::rotateRight(this->right_rotation->right_rotation);
        this->right_rotation->right_rotation->right_rotation->next_block = this->next_block;

        this->right_rotation->right_rotation->right_rotation->right_rotation = this;


        this->left_rotation = this->right_rotation->right_rotation->right_rotation;
        this->left_rotation->next_block = this->next_block;

        this->left_rotation->left_rotation = this->right_rotation->right_rotation;
        this->left_rotation->left_rotation->next_block = this->next_block;

        this->left_rotation->left_rotation->left_rotation = this->right_rotation;
        this->left_rotation->left_rotation->left_rotation->next_block = this->next_block;

        this->left_rotation->left_rotation->left_rotation->left_rotation = this;
    }

    Block* rotateRight(Block* block) {
        int originalRows = block->shape.size();
        int originalCols = block->shape[0].size();

        vector<vector<bool>> rotatedShape(originalCols, vector<bool>(originalRows, false));

        for (int i = 0; i < originalRows; ++i) {
            for (int j = 0; j < originalCols; ++j) {
                rotatedShape[j][originalRows - 1 - i] = block->shape[i][j];
            }
        }
        Block* rotatedBlock = new Block();
        rotatedBlock->shape = rotatedShape;
        return rotatedBlock;
    }
};


#endif //PA2_BLOCK_H
