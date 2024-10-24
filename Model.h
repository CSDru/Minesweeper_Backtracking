//
// Created by Dru on 10/22/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_MODEL_H
#define MINESWEEPER_BACKTRACKING_MODEL_H

#include <vector>
#include "Node.h"

// Tile struct represents each tile on the Minesweeper grid
struct Tile
{
    bool isBomb = false;
    bool isRevealed = false;
    bool isFlagged = false;
    bool isClicked = false;
    bool isHighlighted = false;
    int neighboringBombs = 0;
};

// Enum for the game state: Ongoing, Won, or Lost
enum class GameState { Ongoing, Won, Lost };

class Model
{
private:
    int rows;
    int cols;
    int bombCount;
    bool firstClick = true;
    bool isPaused = false;
    std::vector<std::vector<Tile>> grid;
    GameState gameState = GameState::Ongoing;

public:
    // Constructor with optional default values
    Model(int rows = 16, int cols = 16, int bombCount = 40);

    // Function to place bombs, excluding the area around the first click
    void placeBombs(int startRow, int startCol);

    // Function to calculate the number of neighboring bombs for each tile
    void calculateNeighboringBombs();

    // Utility function to check if a tile is within the bounds of the grid
    bool isInBounds(int row, int col) const;

    // Function to reveal a tile, handling the game's reveal logic and win/loss conditions
    void revealTile(int row, int col);

    // Function to toggle flagging on a tile
    void flagTile(int row, int col);

    // Reset the game to the initial state
    void resetGame();

    // Function to check if the player has won the game
    bool checkWinCondition();

    // Toggle the paused state of the game
    void togglePause() { isPaused = !isPaused; }

    // Retrieve the current paused state
    bool getPausedState() const { return isPaused; }

    // Retrieve the current game state (Ongoing, Won, or Lost)
    GameState getGameState() const { return gameState; }

    // Retrieve the grid representing the Minesweeper board
    const std::vector<std::vector<Tile>>& getGrid() const { return grid; }

    /// Recursion
    void revealNumberedTiles();
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    std::vector<std::pair<int, int>> getNeighbors(int row, int col) const;
    void highlightTile(int row, int col, bool highlight);
    void setGameState(GameState state) { gameState = state; }
};

#endif  // MINESWEEPER_BACKTRACKING_MODEL_H
