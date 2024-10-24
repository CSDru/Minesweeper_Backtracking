//
// Created by Dru on 10/22/2024.
//

#ifndef MINESWEEPER_BACKTRACKING_CONTROLLER_H
#define MINESWEEPER_BACKTRACKING_CONTROLLER_H


#include "Model.h"
#include "View.h"

class Controller
{
private:
    Model& board;
    View& view;

public:
    Controller(Model& board, View& view);

    void handleInput();

    void handlePauseMenu(sf::Event &event);

    /// Backtracking
    bool backtrackBombPlacement(Node& node, std::vector<std::vector<std::pair<int, int>>>& combinations, int index);
    bool isValidPlacement(const std::vector<std::pair<int, int>>& placement);
    void toggleFlags(const std::vector<std::pair<int, int>>& tiles);
    void solveBoard();

};


#endif //MINESWEEPER_BACKTRACKING_CONTROLLER_H
