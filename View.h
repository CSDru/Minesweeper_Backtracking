//
// Created by Dru on 10/22/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_VIEW_H
#define MINESWEEPER_BACKTRACKING_VIEW_H


#include <SFML/Graphics.hpp>
#include "Model.h"
#include "Fonts.h"

class View
{
private:
    Fonts fonts;

    sf::RenderWindow& window;
    Model& board;

    // Sprites and UI elements
    sf::Sprite boardSprite;
    sf::Sprite timerSprites[14];
    sf::Sprite emoji;
    sf::RectangleShape timerBackground;
    const int timerSpriteWidth = 15;
    const int timerSpriteHeight = 22;
    bool isEmojiPressed = false;

    // Button text objects
    sf::Text restartButton;
    sf::Text solveButton;
    sf::Text quitButton;
    sf::RectangleShape exitButton;
    sf::Text exitText;

    // Button objects
    sf::RectangleShape restartButtonBox;
    sf::RectangleShape solveButtonBox;
    sf::RectangleShape quitButtonBox;

public:
    View(sf::RenderWindow& window, Model& board, sf::Texture& boardTexture, sf::Texture& uiTexture);

    void setEmojiPressed(bool pressed);
    void updateEmoji();
    void drawBoard();
    void drawUI();
    void drawPauseMenu();
    void resetButtonStates();

    sf::RenderWindow& getWindow();

    // Getter functions for button words
    const sf::Text& getRestartButton() const { return restartButton; }
    const sf::Text& getSolveButton() const { return solveButton; }
    const sf::Text& getQuitButton() const { return quitButton; }

    // Getter functions for button boxes
    const sf::RectangleShape& getRestartButtonBox() const { return restartButtonBox; }
    const sf::RectangleShape& getSolveButtonBox() const { return solveButtonBox; }
    const sf::RectangleShape& getQuitButtonBox() const { return quitButtonBox; }
    const sf::RectangleShape& getExitButton() const { return exitButton; }

    // Add a method to return the bounding box of the pause menu
    sf::FloatRect getPauseMenuBounds() const;

    void handleHover(int mouseX, int mouseY);

    void displaySolvedBoard();

    void displayNoSolutionMessage();
};


#endif //MINESWEEPER_BACKTRACKING_VIEW_H
