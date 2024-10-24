//
// Created by Dru on 10/22/2024.
//

#include "Controller.h"
#include <SFML/Window/Event.hpp>

Controller::Controller(Model& board, View& view) : board(board), view(view){}

bool pauseToggleHandled = false; // Prevent double-toggle

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
                    } else if (event.mouseButton.button == sf::Mouse::Right)
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
            // Placeholder for Solve button action
            board.togglePause();  // Close the pause menu after solving
            view.resetButtonStates(); // Reset hover state
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
