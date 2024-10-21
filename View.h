//
// Created by Dru on 10/20/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_VIEW_H
#define MINESWEEPER_BACKTRACKING_VIEW_H

#include <SFML/Graphics.hpp>
#include "Model.h"
#include "Controller.h"
#include "SpriteSheetCutter.h"

class View
{
private:
    sf::RenderWindow window;
    SpriteSheetCutter cutter;
    Model& model;
    const std::vector<std::vector<std::vector<std::string>>>& solutions;
    int currentSolution;
    int totalSolutions;

public:
    View(Model& model, Controller& controller, sf::Texture& texture, int windowWidth, int windowHeight);

    // Render the current state of the board
    void render();

    // Handle window events
    void handleEvents();

    // Check if window is open
    bool isOpen() const;

    // Solution Indicator ex: Solution: 2/5
    void displaySolutionIndicator();
};

#endif //MINESWEEPER_BACKTRACKING_VIEW_H
