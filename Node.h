//
// Created by Dru on 10/20/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_NODE_H
#define MINESWEEPER_BACKTRACKING_NODE_H

#include <vector>
#include <utility> // For std::pair

class Node
{
private:
    int x, y; // Coordinates of the number on the board
    int bombCount; // Number of bombs around this square
    std::vector<std::pair<int, int>> neighbors; // Possible bomb locations around this square

    // Helper function to generate all combinations
    void generateCombinations(int start, int n, std::vector<std::pair<int, int>>& currentCombination, std::vector<std::vector<std::pair<int, int>>>& result);
public:
    Node(int x, int y, int bombCount);

    // Returns all possible bomb placement combinations
    std::vector<std::vector<std::pair<int, int>>> getBombCombinations();

    // Reset teh node after backtracking
    void reset();

};


#endif //MINESWEEPER_BACKTRACKING_NODE_H
