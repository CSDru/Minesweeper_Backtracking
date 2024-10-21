//
// Created by Dru on 10/20/2024.
//

#include "Controller.h"

Controller::Controller(Model& model) : model(model){}

void Controller::solve(int index)
{
    auto& nodes = model.getNodes();

    if (index == nodes.size())
    {
        //If all nodes are solved, store the current solution
        solutions.push_back(model.getBoard());
        return;
    }

    Node& node = nodes[index];
    auto combinations = node.getBombCombinations();

    for (const auto& combination : combinations)
    {
        if (canPlaceBombs(combination))
        {
            placeBombs(combination);
            solve(index + 1); // Recursively solve for the next node
            removeBombs(combination); // Backtrack
        }
    }
}

bool Controller::canPlaceBombs(const std::vector<std::pair<int, int>>& combination)
{
    // Check if placing bombs in these spots breaks any game rules (e.g., overlapping bombs)
    for (const auto& [x, y] : combination)
    {
        if (model.getBoard()[x][y] == "X") // No bombs on existing bombs
        {
            return false;
        }
    }
    return true;
}

void Controller::placeBombs(const std::vector<std::pair<int, int>>& combination)
{
    for (const auto& [x, y] : combination)
    {
        model.placeBomb(x, y);
    }
}

void Controller::removeBombs(const std::vector<std::pair<int, int>>& combination)
{
    for (const auto& [x, y] : combination)
    {
        model.removeBomb(x, y);
    }
}

const std::vector<std::vector<std::vector<std::string>>> &Controller::getSolutions() const
{
    return solutions;
}
