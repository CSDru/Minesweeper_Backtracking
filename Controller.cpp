//
// Created by Dru on 10/22/2024.
//

#include "Controller.h"
#include <SFML/Window/Event.hpp>

Controller::Controller(Model& board, View& view) : board(board), view(view){}

void Controller::handleInput()
{
    sf::Event event;
    sf::RenderWindow& window = view.getWindow();

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        // Check if the game is paused
        if (board.getPausedState())
        {
            if (event.type == sf::Event::MouseMoved)
            {
                int mouseX = event.mouseMove.x;
                int mouseY = event.mouseMove.y;
                view.handleHover(mouseX, mouseY);
            }
            handlePauseMenu(event);
        }
        else
        {
            // Handle gameplay input
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if emoji is clicked
                if (mouseX >= window.getSize().x / 2 - 24 && mouseX < window.getSize().x / 2 + 24 && mouseY >= 10 && mouseY <= 58)
                {
                    view.setEmojiPressed(true);
                }
                else
                {
                    // Normal Gameplay input
                    // Ignore clicks in menu area for gameplay input
                    if (mouseY <= 65)
                    {
                        return;
                    }

                    // Convert mouse click to grid coordinates
                    int col = mouseX / 65;
                    int row = (mouseY - 65) / 65; // Adjust for UI bar

                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        board.revealTile(row, col); // Reveal clicked tile
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        board.flagTile(row, col);
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Check if the emoji is clicked
                if (mouseX >= window.getSize().x / 2 - 24 && mouseX <= window.getSize().x / 2 + 24 &&
                    mouseY >= 10 && mouseY <= 58)
                {
                    view.setEmojiPressed(false);  // Revert to non-pressed emoji
                    board.togglePause();  // You can also open the pause menu here if needed
                }
            }
        }
    }
}

void Controller::handlePauseMenu(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        int mouseX = event.mouseButton.x;
        int mouseY = event.mouseButton.y;

        // Handle clicking the Restart button box
        if (view.getRestartButtonBox().getGlobalBounds().contains(mouseX, mouseY))
        {
            board.resetGame();  // Restart the game
            board.togglePause();  // Close the pause menu after restarting
            view.resetButtonStates(); // Reset hover state
        }

        // Handle clicking the Solve button box
        if (view.getSolveButtonBox().getGlobalBounds().contains(mouseX, mouseY))
        {
            board.togglePause();  // Close the pause menu after solving
            view.resetButtonStates(); // Reset hover state
            board.revealNumberedTiles(); // Reveal only the numbered tiles
            solveBoard(); // Activate solving algorithm
        }

        // Handle clicking the Quit button box
        if (view.getQuitButtonBox().getGlobalBounds().contains(mouseX, mouseY))
        {
            view.getWindow().close();  // Quit the game
        }

        // Handle clicking the Exit button
        if (view.getExitButton().getGlobalBounds().contains(mouseX, mouseY))
        {
            board.togglePause();  // Close the pause menu
            view.resetButtonStates(); // Reset hover state
        }

        // Click outside the pause menu closes the menu
        if (!view.getPauseMenuBounds().contains(mouseX, mouseY))
        {
            board.togglePause();  // Close the pause menu if clicked outside
            view.resetButtonStates(); // Reset hover state
        }
    }
}

// Recursive backtracking method to test bomb placements
bool Controller::backtrackBombPlacement(Node& node, std::vector<std::vector<std::pair<int, int>>>& combinations, int index)
{
    sf::Window& window = view.getWindow();
    if (index >= combinations.size())
    {
        return false; // No more combinations to try -> backtrack
    }

    // Highlight the current tile
    board.highlightTile(node.getCoordinate().first, node.getCoordinate().second, true);

    // Draw the updated board with highlighted tile
    view.drawBoard();
    window.display();

    // Add a small delay to slow down algorithm for visualization
    sf::sleep(sf::milliseconds(200));

    // Try the current combination
    std::vector<std::pair<int, int>> currentPlacement = combinations[index];

    // Toggle the flag for the locations
    toggleFlags(currentPlacement);

    // Check if the placement is valid
    bool valid = isValidPlacement(combinations[index]);

    // Draw the board
    view.drawBoard();
    window.display();

    // Add a small delay to slow down algorithm for visualization
    sf::sleep(sf::milliseconds(200));

    if (valid)
    {
        // Unhighlight the current tile after processing
        board.highlightTile(node.getCoordinate().first, node.getCoordinate().second, false);

        return true;
    }
    else
    {
        // Backtrack by removing the bombs and tyring the next combination
        toggleFlags(currentPlacement);

        // Unhighlight the current tile after processing
        board.highlightTile(node.getCoordinate().first, node.getCoordinate().second, false);

        return backtrackBombPlacement(node, combinations, index + 1);
    }
}

bool Controller::isValidPlacement(const std::vector<std::pair<int, int>> &placement)
{
    for (const auto& coord : placement)
    {
        int row = coord.first;
        int col = coord.second;

        // Count flagged neighbors
        int flaggedCount = 0;
        for (const auto& neighbor : board.getNeighbors(row, col))
        {
            if (board.getGrid()[neighbor.first][neighbor.second].isFlagged)
            {
                flaggedCount++;
            }
        }

        // If flagged tiles don't match expected bombs, return false
        if (flaggedCount != board.getGrid()[row][col].neighboringBombs)
        {
            return false;
        }
    }
    return true;
}

void Controller::toggleFlags(const std::vector<std::pair<int, int>> &tiles)
{
    for (const auto& tile : tiles)
    {
        board.flagTile(tile.first, tile.second); // Toggle Flag
    }
}

void Controller::solveBoard()
{
    bool solved = true;

    for (int row = 0; row < board.getRows(); ++row)
    {
        for(int col = 0; col < board.getCols(); ++col)
        {
            // Check if the tile is a numbered tile
            if (board.getGrid()[row][col].neighboringBombs > 0)
            {
                std::vector<std::pair<int, int>> neighbors = board.getNeighbors(row, col);
                Node node({row, col});
                std::vector<std::vector<std::pair<int, int>>> combinations = node.generateBombPlacements(neighbors, board.getGrid()[row][col].neighboringBombs);

                // Run backtracking algorithm
                if (!backtrackBombPlacement(node, combinations, 0))
                {
                    solved = false; // If no valid solution, board is unsolvable
                }
            }
        }

        // if algorithm i successful, Win game
        if (solved)
        {
            board.setGameState(GameState::Won);
        }
    }
}
