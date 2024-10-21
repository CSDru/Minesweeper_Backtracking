//
// Created by Dru on 10/20/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_CONTROLLER_H
#define MINESWEEPER_BACKTRACKING_CONTROLLER_H

#include <vector>
#include <string>
#include "Model.h"

class Controller
{
private:
    Model& model; // Reference to the model
    std::vector<std::vector<std::vector<std::string>>> solutions; // Store all possible board solutions
    std::vector<std::pair<int, int>> nodes; // List of Nodes containing numbered squares

    // Check if bombs can be placed in a combination without breaking the game rules
    bool canPlaceBombs(const std::vector<std::pair<int, int>>& combination);

    // Place bombs in the current combination
    void placeBombs(const std::vector<std::pair<int, int>>& combination);

    // Remove bombs to backtrack
    void removeBombs(const std::vector<std::pair<int, int>>& combination);

public:
    Controller(Model& model);

    // Solves the Minesweeper board using backtracking
    void solve(int index = 0);

    // Get all stored solutions
    const std::vector<std::vector<std::vector<std::string>>>& getSolutions() const;
};


#endif //MINESWEEPER_BACKTRACKING_CONTROLLER_H
