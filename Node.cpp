//
// Created by Dru on 10/23/2024.
//

#include "Node.h"

// Constructor to initialize the Node with a given coordinate
Node::Node(std::pair<int, int> coord) : coordinate(coord), currentIndex(0) {}

// Getter for the coordinate
std::pair<int, int> Node::getCoordinate()
{
    return coordinate;
}

// Helper recursive function to generate combinations of bomb placements
void generateCombinations(int start, int bombsLeft, std::vector<std::pair<int, int>>& currentCombination,
                          std::vector<std::pair<int, int>>& neighbors,
                          std::vector<std::vector<std::pair<int, int>>>& allCombinations)
{
    if (bombsLeft == 0)
    {
        allCombinations.push_back(currentCombination);
        return;
    }
    for (int i = start; i <= neighbors.size() - bombsLeft; ++i)
    {
        currentCombination.push_back(neighbors[i]);
        generateCombinations(i + 1, bombsLeft - 1, currentCombination, neighbors, allCombinations);
        currentCombination.pop_back();
    }
}

// Method to generate and return all combinations of bomb placements using recursion
std::vector<std::vector<std::pair<int, int>>> Node::generateBombPlacements(std::vector<std::pair<int, int>> neighbors, int bombs)
{
    bombPlacements.clear();  // Reset bombPlacements
    std::vector<std::pair<int, int>> currentCombination;
    generateCombinations(0, bombs, currentCombination, neighbors, bombPlacements);
    resetIterator();  // Reset iterator after generating combinations
    return bombPlacements;
}

// Reset the iterator to the beginning
void Node::resetIterator()
{
    currentIndex = 0;
}

// Get the next combination and increment the index
std::vector<std::pair<int, int>> Node::nextCombination()
{
    if (currentIndex < bombPlacements.size())
    {
        return bombPlacements[currentIndex++];
    }
    return {};
}

// Check if there are more combinations to traverse
bool Node::hasMoreCombinations()
{
    return currentIndex < bombPlacements.size();
}
