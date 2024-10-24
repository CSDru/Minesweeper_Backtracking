//
// Created by Dru on 10/22/2024.
//

#include "View.h"

View::View(sf::RenderWindow& window, Model& board, sf::Texture& boardTexture, sf::Texture& uiTexture)
        : window(window), board(board)
{
    // Initialize the button boxes with a darker grey color
    restartButtonBox.setSize(sf::Vector2f(200, 50));
    restartButtonBox.setOutlineColor(sf::Color::Black);
    restartButtonBox.setOutlineThickness(2);
    restartButtonBox.setFillColor(sf::Color(160, 160, 160));  // Darker grey fill color
    restartButtonBox.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 60);

    solveButtonBox.setSize(sf::Vector2f(200, 50));
    solveButtonBox.setOutlineColor(sf::Color::Black);
    solveButtonBox.setOutlineThickness(2);
    solveButtonBox.setFillColor(sf::Color(160, 160, 160));  // Darker grey fill color
    solveButtonBox.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2);

    quitButtonBox.setSize(sf::Vector2f(200, 50));
    quitButtonBox.setOutlineColor(sf::Color::Black);
    quitButtonBox.setOutlineThickness(2);
    quitButtonBox.setFillColor(sf::Color(160, 160, 160));  // Darker grey fill color
    quitButtonBox.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 + 60);

    // Initialize the sprite sheet cutter for the board (11 rows, 12 columns)
    boardSprite.setTexture(boardTexture);

    // Initialize the timer sprites
    for (int i = 0; i < 14; ++i)
    {
        timerSprites[i].setTexture(uiTexture);
        timerSprites[i].setTextureRect(sf::IntRect(i * timerSpriteWidth, 0, timerSpriteWidth, timerSpriteHeight));
        timerSprites[i].setScale(2.f, 2.f);  // Scale 2x
    }

    // Create the grey bar across the top
    timerBackground.setSize(sf::Vector2f(window.getSize().x - 10, 55));
    timerBackground.setFillColor(sf::Color(192, 192, 192));
    timerBackground.setPosition(5, 5);

    // Initialize emoji
    const int emojiSpriteSize = 24;
    emoji.setTexture(uiTexture);
    emoji.setTextureRect(sf::IntRect(0, emojiSpriteSize, emojiSpriteSize, emojiSpriteSize));
    emoji.setScale(2.f, 2.f);
    emoji.setPosition((window.getSize().x / 2) - (emojiSpriteSize * 2 / 2), 10);

    // Initialize Pause Menu buttons
    sf::Font& font = fonts.getFont(Fonts::ARIAL);

    // Restart button
    restartButton.setFont(font);
    restartButton.setString("RESTART");
    restartButton.setCharacterSize(30);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(window.getSize().x / 2 - 200 + 150, window.getSize().y / 2 - 150 + 100);

    // Solve button
    solveButton.setFont(font);
    solveButton.setString("SOLVE");
    solveButton.setCharacterSize(30);
    solveButton.setFillColor(sf::Color::White);
    solveButton.setPosition(window.getSize().x / 2 - 200 + 150, window.getSize().y / 2 - 150 + 150);

    // Quit button
    quitButton.setFont(font);
    quitButton.setString("QUIT");
    quitButton.setCharacterSize(30);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(window.getSize().x / 2 - 200 + 150, window.getSize().y / 2 - 150 + 200);

    // Exit button
    exitButton.setSize(sf::Vector2f(40, 40));
    exitButton.setFillColor(sf::Color(192, 192, 192));  // Same grey as the menu
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setOutlineThickness(2);
    exitButton.setPosition(window.getSize().x / 2 - 200 + 360, window.getSize().y / 2 - 150 + 10);

    exitText.setFont(font);
    exitText.setString("X");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + 8, exitButton.getPosition().y);
}

void View::setEmojiPressed(bool pressed)
{
    isEmojiPressed = pressed;
    updateEmoji();
}

void View::updateEmoji()
{
    // Determine which sprite to use based on the game state and press status
    if (isEmojiPressed)
    {
        switch (board.getGameState())
        {
            case GameState::Ongoing:
                emoji.setTextureRect(sf::IntRect(1 * 25, 24, 24, 24));  // Pressed smiley face
                break;
            case GameState::Lost:
                emoji.setTextureRect(sf::IntRect(7 * 25, 24, 24, 24));  // Pressed dead face
                break;
            case GameState::Won:
                emoji.setTextureRect(sf::IntRect(5 * 25, 24, 24, 24));  // Pressed sunglasses face
                break;
        }
    }
    else
    {
        switch (board.getGameState())
        {
            case GameState::Ongoing:
                emoji.setTextureRect(sf::IntRect(0 * 25, 24, 24, 24));  // Non-pressed smiley face
                break;
            case GameState::Lost:
                emoji.setTextureRect(sf::IntRect(6 * 25, 24, 24, 24));  // Non-pressed dead face
                break;
            case GameState::Won:
                emoji.setTextureRect(sf::IntRect(4 * 25, 24, 24, 24));  // Non-pressed sunglasses face
                break;
        }
    }
}

void View::drawBoard()
{

    for (int row = 0; row < 16; ++row)
    {
        for (int col = 0; col < 16; ++col)
        {
            const Tile& tile = board.grid[row][col];

            if (tile.isRevealed)
            {
                updateEmoji();
                if (tile.isBomb)
                {
                    if (tile.isClicked)
                    {
                        // Special sprite for the bomb that was clicked
                        boardSprite.setTextureRect(sf::IntRect(6 * 68, 0, 65, 65));  // Set this to the explosion sprite position
                    }
                    else
                    {
                        // Bomb position on Sprite Sheet
                        boardSprite.setTextureRect(sf::IntRect(5 * 68, 0, 65, 65));
                    }
                }
                else
                {
                    // Number neighboring bombs
                    tile.neighboringBombs == 0 ? boardSprite.setTextureRect(sf::IntRect(1 * 68, 0, 65, 65)) : boardSprite.setTextureRect(sf::IntRect((tile.neighboringBombs - 1) * 68, 1 * 68, 65, 65));
                }
            }
            else if (tile.isFlagged)
            {
                // Flag position on Sprite Sheet
                boardSprite.setTextureRect(sf::IntRect(2 * 68, 0, 65, 65));
            }
            else
            {
                // Unblocked Square position on Sprite Sheet
                boardSprite.setTextureRect(sf::IntRect(0, 0, 65, 65));
            }

            boardSprite.setPosition(col * 65, (row + 1) * 65);
            window.draw(boardSprite);
        }
    }
}

void View::drawUI()
{
    // Draw the grey bar
    window.draw(timerBackground);

    // Render the left timer
    for (int i = 0; i < 3; ++i)
    {
        timerSprites[0].setPosition(30 + i * (timerSpriteWidth * 2), 11);
        window.draw(timerSprites[0]);
    }

    // Render the right timer
    for (int i = 0; i < 3; ++i)
    {
        timerSprites[0].setPosition(window.getSize().x - 120 + i * (timerSpriteWidth * 2), 11);
        window.draw(timerSprites[0]);
    }

    // Draw the emoji
    window.draw(emoji);

    // If teh game is paused, draw pause menu
    if (board.getPausedState())
    {
        drawPauseMenu();
    }
}

void View::drawPauseMenu()
{
    // Draw the grey background for the pause menu first
    sf::RectangleShape pauseMenu(sf::Vector2f(400, 300));
    pauseMenu.setFillColor(sf::Color(192, 192, 192)); // Lighter grey for background
    pauseMenu.setOutlineColor(sf::Color::Black); // Black outline
    pauseMenu.setOutlineThickness(5);
    pauseMenu.setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 150);

    // Draw the grey background first
    window.draw(pauseMenu);

    // "Paused" text
    sf::Font& font = fonts.getFont(Fonts::ARIAL);
    sf::Text pauseText("Paused", font, 50);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(pauseMenu.getPosition().x + 120, pauseMenu.getPosition().y + 20);

    // Draw the "Paused" text
    window.draw(pauseText);

    // Center the button text in the button boxes
    sf::FloatRect restartBounds = restartButton.getLocalBounds();
    restartButton.setPosition(
            restartButtonBox.getPosition().x + (restartButtonBox.getSize().x / 2) - (restartBounds.width / 2),
            restartButtonBox.getPosition().y + (restartButtonBox.getSize().y / 2) - (restartBounds.height / 2) - restartBounds.top
    );

    sf::FloatRect solveBounds = solveButton.getLocalBounds();
    solveButton.setPosition(
            solveButtonBox.getPosition().x + (solveButtonBox.getSize().x / 2) - (solveBounds.width / 2),
            solveButtonBox.getPosition().y + (solveButtonBox.getSize().y / 2) - (solveBounds.height / 2) - solveBounds.top
    );

    sf::FloatRect quitBounds = quitButton.getLocalBounds();
    quitButton.setPosition(
            quitButtonBox.getPosition().x + (quitButtonBox.getSize().x / 2) - (quitBounds.width / 2),
            quitButtonBox.getPosition().y + (quitButtonBox.getSize().y / 2) - (quitBounds.height / 2) - quitBounds.top
    );

    // Exit button
    exitButton.setPosition(
            pauseMenu.getPosition().x + pauseMenu.getSize().x - exitButton.getSize().x,  // 10px padding from right
            pauseMenu.getPosition().y  // 10px padding from top
    );

    exitButton.setOutlineThickness(0); // No outline

    // Center the "X" text inside the exit button
    sf::FloatRect exitTextBounds = exitText.getLocalBounds();
    exitText.setPosition(
            exitButton.getPosition().x + (exitButton.getSize().x / 2) - (exitTextBounds.width / 2),
            exitButton.getPosition().y + (exitButton.getSize().y / 2) - (exitTextBounds.height / 2) - exitTextBounds.top
    );

    // Draw the button boxes and text
    window.draw(restartButtonBox);
    window.draw(solveButtonBox);
    window.draw(quitButtonBox);

    window.draw(restartButton);
    window.draw(solveButton);
    window.draw(quitButton);

    // Draw the exit button (rectangle and text)
    window.draw(exitButton);
    window.draw(exitText);
}

void View::resetButtonStates()
{
    // Reset all button boxes to their default outline color (black)
    restartButtonBox.setOutlineColor(sf::Color::Black);
    solveButtonBox.setOutlineColor(sf::Color::Black);
    quitButtonBox.setOutlineColor(sf::Color::Black);

    // Reset the exit button color to its default state (grey)
    exitButton.setFillColor(sf::Color(192, 192, 192));

    // Just in case, update emoji
    updateEmoji();
}

void View::handleHover(int mouseX, int mouseY)
{
    // Hover effect for Restart button box
    if (restartButtonBox.getGlobalBounds().contains(mouseX, mouseY))
    {
        restartButtonBox.setOutlineColor(sf::Color::White);  // White outline when hovered
    }
    else
    {
        restartButtonBox.setOutlineColor(sf::Color::Black);  // Revert to black
    }

    // Hover effect for Solve button box
    if (solveButtonBox.getGlobalBounds().contains(mouseX, mouseY))
    {
        solveButtonBox.setOutlineColor(sf::Color::White);  // White outline when hovered
    }
    else
    {
        solveButtonBox.setOutlineColor(sf::Color::Black);  // Revert to black
    }

    // Hover effect for Quit button box
    if (quitButtonBox.getGlobalBounds().contains(mouseX, mouseY))
    {
        quitButtonBox.setOutlineColor(sf::Color::White);  // White outline when hovered
    }
    else
    {
        quitButtonBox.setOutlineColor(sf::Color::Black);  // Revert to black
    }

    // Exit button hover effect (unchanged)
    if (getExitButton().getGlobalBounds().contains(mouseX, mouseY))
    {
        exitButton.setFillColor(sf::Color::Red);  // Red when hovered
    }
    else
    {
        exitButton.setFillColor(sf::Color(192, 192, 192));  // Revert to grey
    }
}

void View::displaySolvedBoard()
{

    for (int row = 0; row < 16; ++row)
    {
        for(int col = 0; col < 16; ++col)
        {
            const Tile& tile = board.grid[row][col];

            if (tile.isRevealed)
            {
                if (tile.isBomb)
                {
                    boardSprite.setTextureRect(sf::IntRect(7 * 68, 0, 65, 65));
                }
                else
                {
                    if (tile.neighboringBombs > 0)
                    {
                        boardSprite.setTextureRect(sf::IntRect((tile.neighboringBombs - 1) * 68, 1 * 68, 65, 65));
                    }
                    else
                    {
                        boardSprite.setTextureRect(sf::IntRect(1 * 68, 0, 65, 65));
                    }
                }
            }
            else
            {
                boardSprite.setTextureRect(sf::IntRect(0, 0, 65, 65)); // Default unclicked state
            }

            boardSprite.setPosition(col * 65, (row + 1) * 65); // Next square
            window.draw(boardSprite);
        }
    }

    window.display(); // Update display
}

void View::displayNoSolutionMessage()
{
    sf::Text noSolutionText("No Valid solution found", fonts.getFont(Fonts::ARIAL), 40);
    noSolutionText.setFillColor(sf::Color::Red);
    noSolutionText.setPosition(100, 100);
    window.draw(noSolutionText);
    window.display();
}

sf::FloatRect View::getPauseMenuBounds() const
{
    // The position and size of the pause menu
    sf::RectangleShape pauseMenu(sf::Vector2f(400, 300));
    pauseMenu.setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 150);

    return pauseMenu.getGlobalBounds();
}


sf::RenderWindow &View::getWindow()
{
    return window;
}
