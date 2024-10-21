//
// Created by Dru on 10/20/2024.
//

#include "Model.h"
#include <iostream>
#include <cctype> // For isdigit
#include <string>
#include <algorithm>

Model::Model(int rows, int cols, const std::vector<std::vector<std::string>>& boardSetup) : board(boardSetup)
{
    // Create Nodes based on the board configuration
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            const std::string& cell = board[i][j];

            if (!cell.empty() && std::all_of(cell.begin(), cell.end(), ::isdigit))
            {
                int bombCount = std::stoi(cell); // Convert string to integer
                nodes.emplace_back(i, j, bombCount);
            }
        }
    }
}

std::vector<std::vector<std::string>>& Model::getBoard()
{
    return board;
}

std::vector<Node>& Model::getNodes()
{
    return nodes;
}

void Model::placeBomb(int x, int y)
{
    board[x][y] = "X"; // 'X' denotes a bomb
}

void Model::removeBomb(int x, int y)
{
    board[x][y] = "-"; // '-' denotes an empty space
}

bool Model::isSolved()
{
    // Basic check for debugging; you can refine this based on actual game rules
    for (const auto& row : board)
    {
        for (const auto& cell : row)
        {
            if (cell == "-") // If any cells are empty, it's not solved
            {
                return false;
            }
        }
    }
    return true;
}

void Model::printBoard()
{
    for (const auto& row : board)
    {
        for (const auto& cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}