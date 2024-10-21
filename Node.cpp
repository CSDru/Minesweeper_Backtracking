//
// Created by Dru on 10/20/2024.
//

#include "Node.h"

Node::Node(int x, int y, int bombCount) : x(x), y(y), bombCount(bombCount)
{
    // Populate neighbors (8 potential spots around this node)
    for(int dx = -1; dx <= 1; ++dx)
    {
        for(int dy = -1; dy <=1; ++dy)
        {
            if(dx !=0 || dy !=0) // Exclude teh center
                neighbors.push_back({x + dx, y + dy});
        }
    }
}

void Node::reset()
{
    // Reset any state necessary (if you track which spots were "bombed")
    // Currently, no state is tracked, so this is empty
}

void Node::generateCombinations(int start, int n, std::vector<std::pair<int, int>> &currentCombination, std::vector<std::vector<std::pair<int, int>>> &result)
{
    if(currentCombination.size() == n)
    {
        result.push_back(currentCombination);
        return;
    }

    for(int i = start; i < neighbors.size(); ++i)
    {
        currentCombination.push_back(neighbors[i]);
        generateCombinations(i + 1, n, currentCombination, result);
        currentCombination.pop_back(); // Backtrack
    }
}

std::vector<std::vector<std::pair<int, int>>> Node::getBombCombinations()
{
    std::vector<std::vector<std::pair<int, int>>> result;
    std::vector<std::pair<int, int>> currentCombination;
    generateCombinations(0, bombCount, currentCombination, result);
    return result;
}
