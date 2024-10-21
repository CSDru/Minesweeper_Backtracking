#include <SFML/Graphics.hpp>
#include <iostream>
#include "Model.h"
#include "Controller.h"
#include "View.h"

int main(int argc, char* argv[])
{
    std::string executablePath = argv[0];
    std::cout << "Executable path: " << executablePath << std::endl;

    // Load the sprite sheet texture
    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/Dru/CLionProjects/Minesweeper_Backtracking/cmake-build-debug/minesweep_cut.png"))
    {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }

    // Example board setup with multi-digit numbers
    std::vector<std::vector<std::string>> board = {
            { "∞", "-", "-" },
            { "-", "100", "-" },
            { "-", "-", "2763" }
    };

    // Initialize the Model, Controller, and View
    Model model(3, 3, board);
    Controller controller(model);
    controller.solve();
    View view(model, controller, texture, 70 * 3, 70 * 3); // 3x3 grid with 16x16 sprites, so window is 48x48

    // Solve the board
    controller.solve();

    // Main loop for rendering
    while (view.isOpen())
    {
        view.handleEvents();
        view.render(); // Render the current state of the board
    }

    return 0;
}
