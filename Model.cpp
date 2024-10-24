//
// Created by Dru on 10/22/2024.
//

#include "Model.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Model::Model(int rows, int cols, int bombCount)
        : rows(rows), cols(cols), bombCount(bombCount)
{
    grid.resize(rows, std::vector<Tile>(cols));
    std::srand(std::time(0));  // Seed the random number generator for bomb placement
}

void Model::placeBombs(int startRow, int startCol)
{
    int placedBombs = 0;
    while (placedBombs < bombCount)
    {
        int row = std::rand() % rows;
        int col = std::rand() % cols;
        if (!grid[row][col].isBomb && (std::abs(row - startRow) > 1 || std::abs(col - startCol) > 1))
        {
            grid[row][col].isBomb = true;
            placedBombs++;
        }
    }
    calculateNeighboringBombs();  // Recalculate neighboring bomb counts after placing bombs
}

void Model::calculateNeighboringBombs()
{
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (grid[row][col].isBomb) continue;

            int bombCount = 0;
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (isInBounds(newRow, newCol) && grid[newRow][newCol].isBomb)
                    {
                        bombCount++;
                    }
                }
            }
            grid[row][col].neighboringBombs = bombCount;
        }
    }
}

bool Model::isInBounds(int row, int col) const
{
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void Model::revealTile(int row, int col)
{
    if(gameState != GameState::Ongoing) return;  // No action if game is over

    if (!isInBounds(row, col) || grid[row][col].isFlagged) return;

    // Handle the first click and place bombs
    if (firstClick)
    {
        placeBombs(row, col);
        firstClick = false;
    }

    if (grid[row][col].isRevealed)
    {
        // If this tile is revealed and has neighboring bombs, check if flags match bomb count
        if (grid[row][col].neighboringBombs > 0)
        {
            int flagCount = 0;
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (isInBounds(newRow, newCol) && grid[newRow][newCol].isFlagged)
                    {
                        flagCount++;
                    }
                }
            }

            if (flagCount == grid[row][col].neighboringBombs)
            {
                for (int i = -1; i <= 1; ++i)
                {
                    for (int j = -1; j <= 1; ++j)
                    {
                        int newRow = row + i;
                        int newCol = col + j;
                        if (isInBounds(newRow, newCol) && !grid[newRow][newCol].isRevealed && !grid[newRow][newCol].isFlagged)
                        {
                            revealTile(newRow, newCol);  // Reveal non-flagged, non-revealed neighbors
                        }
                    }
                }
            }
        }
        return;
    }

    // Reveal tile logic for non-revealed tiles
    grid[row][col].isRevealed = true;

    // If the tile is a bomb, the game is lost
    if (grid[row][col].isBomb)
    {
        gameState = GameState::Lost;

        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                if (grid[r][c].isBomb)
                {
                    grid[r][c].isRevealed = true;  // Reveal all bombs
                }
            }
        }
        return;
    }

    // If no neighboring bombs, perform flood fill to reveal adjacent tiles
    if (grid[row][col].neighboringBombs == 0 && !grid[row][col].isBomb)
    {
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                int newRow = row + i;
                int newCol = col + j;
                if (isInBounds(newRow, newCol))
                {
                    revealTile(newRow, newCol);  // Recursively reveal neighboring tiles
                }
            }
        }
    }

    if (checkWinCondition())
    {
        gameState = GameState::Won;
    }
}

bool Model::checkWinCondition()
{
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            // If a non-bomb tile is still unrevealed, the player hasn't won the game yet
            if (!grid[row][col].isRevealed && !grid[row][col].isBomb)
                return false;
        }
    }
    return true;
}

void Model::flagTile(int row, int col)
{
    if (isInBounds(row, col) && !grid[row][col].isRevealed)
    {
        grid[row][col].isFlagged = !grid[row][col].isFlagged;  // Toggle flag
    }
}

void Model::resetGame()
{
    grid.clear();
    grid.resize(rows, std::vector<Tile>(cols));  // Reinitialize the grid
    firstClick = true;  // Allow bombs to be placed again after reset
    gameState = GameState::Ongoing;  // Set game state back to ongoing
}
