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
};


#endif //MINESWEEPER_BACKTRACKING_CONTROLLER_H
