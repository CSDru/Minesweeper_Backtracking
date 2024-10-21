//
// Created by Dru on 10/20/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_MODEL_H
#define MINESWEEPER_BACKTRACKING_MODEL_H

#include <vector>
#include <string>
#include "Node.h"

class Model
{
private:
    std::vector<std::vector<std::string>> board; // 2D vector for the Minesweeper grid
    std::vector<Node> nodes; // Nodes representing numbered squares on the board

public:
    Model(int rows, int cols, const std::vector<std::vector<std::string>>& boardSetup);

    // Accessor for the board
    std::vector<std::vector<std::string>>& getBoard();

    // Accessor for the nodes
    std::vector<Node>& getNodes();

    // Modify the board (e.g., place a bomb)
    void placeBomb(int x, int y);

    // Remove a bomb (for backtracking)
    void removeBomb(int x, int y);

    // Check if the board is fully solved
    bool isSolved();

    // Print the current state of the board (for debugging)
    void printBoard();
};

#endif //MINESWEEPER_BACKTRACKING_MODEL_H
