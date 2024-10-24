#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1040, 1120), "Minesweeper");

    // Load the sprite sheets
    sf::Texture boardTexture;
    if (!boardTexture.loadFromFile("minesweep_cut.png"))
        return -1;

    sf::Texture uiTexture;
    if (!uiTexture.loadFromFile("minesweep.png"))
        return -1;

    // Initialize MVC components
    Model board;
    View view(window, board, boardTexture, uiTexture);
    Controller controller(board, view);

    // Main game loop
    while (window.isOpen())
    {
        controller.handleInput();
        window.clear();
        view.drawBoard();
        view.drawUI();
        window.display();
    }

    return 0;
}
