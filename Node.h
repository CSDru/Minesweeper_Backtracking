//
// Created by Dru on 10/23/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_NODE_H
#define MINESWEEPER_BACKTRACKING_NODE_H

#include <vector>
#include <utility>

class Node {
private:
    // Stores the coordinate of the numbered square
    std::pair<int, int> coordinate;
    // Stores all possible bomb placements
    std::vector<std::vector<std::pair<int, int>>> bombPlacements;
    // Iterator index for traversal
    int currentIndex;

public:
    // Constructor to initialize the Node with a given coordinate
    Node(std::pair<int, int> coord);

    // Getter for the coordinate
    std::pair<int, int> getCoordinate();

    // Method to generate and return all combinations of bomb placements
    std::vector<std::vector<std::pair<int, int>>> generateBombPlacements(std::vector<std::pair<int, int>> neighbors, int bombs);

    // Reset the iterator to the beginning of the bomb combinations
    void resetIterator();

    // Get the next combination and increment the index
    std::vector<std::pair<int, int>> nextCombination();

    // Check if there are more combinations to traverse
    bool hasMoreCombinations();
};

#endif  // MINESWEEPER_BACKTRACKING_NODE_H
