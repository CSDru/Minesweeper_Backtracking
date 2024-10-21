//
// Created by Dru on 10/20/2024.
//

#include "View.h"
#include <iostream>
#include "Fonts.h"

View::View(Model &model, Controller &controller, sf::Texture &texture, int windowWidth, int windowHeight) : window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper"), model(model), cutter(texture, 11, 12), solutions(controller.getSolutions()), currentSolution(0)
{
    totalSolutions = solutions.size();
}

bool View::isOpen() const
{
    return window.isOpen();
}

void View::render()
{
    window.clear(sf::Color::Black);

    // Get the current solution to display
    const auto& solution = solutions[currentSolution];
    const auto& board = model.getBoard();
    for(int i = 0; i < board.size(); ++i)
    {
        for(int j = 0; j < board[0].size(); ++j)
        {
            const std::string cell = board[i][j];

            if(cell == "-")
                cutter.set(0, 0); // Empty space is at row 0, col 0
            else if(cell == "X")
                cutter.set(0, 5); //Bomb is at row 0, col 5
            else if(cell == "∞")
                cutter.set(10, 11); // ∞ is at row 10 col 11
            else if(!cell.empty() && std::all_of(cell.begin(), cell.end(), ::isdigit))
            {
                int number = std::stoi(cell); //convert string to integer

                if(number == 0)
                    cutter.set(0, 8); // 0 Is at 0, 8
                else if(number < 100)
                {
                    int index = number - 1; // Index starts from 0 for 1
                    cutter.set(1, index); // Numbers 1 - 100 start at row 1, col 0
                }
                else if(number < 900 && number % 100 == 0)
                {
                    int index = (number / 100) - 1; // Index starts from 0 for 100
                    cutter.set(9, 3 + index);
                }
                else if((number <= 9000 && number % 1000 == 0) || (number == 2763))
                {
                    int index = (number / 1000) - 1; // Index for 1,000 starts at 0

                    if(number <= 2000)
                        cutter.set(10, index); // 1000 and 2000 are at row 10 col 0 and 1
                    else if(number == 2763)
                    {
                        // Special case for 2,763 (right after 2000)
                        cutter.set(10, 2); // row 10 col 2
                    }
                    else if (number > 2000)
                        cutter.set(10, index + 1); // Numbers 3,000 and beyond shift by 1 index
                }
                else if(number == 9999)
                    cutter.set(10, 10); // 9999 is at row 10 col 10
            }

            // Set the sprite position and draw it
            cutter.setPosition(j * 70, i * 70); // 16x16 sprite size
            window.draw(cutter);
        }
    }
    displaySolutionIndicator();

    window.display();
}

void View::handleEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Right)
                // Go to next solution
                currentSolution = (currentSolution + 1) % totalSolutions;
            else if(event.key.code == sf::Keyboard::Left)
                // go to previous solution
                currentSolution = (currentSolution - 1 + totalSolutions) % totalSolutions;
        }
    }
}

void View::displaySolutionIndicator()
{
    sf::Font& font = Fonts::getFont(Fonts::ARIAL);

    sf::Text text;
    text.setFont(font);
    text.setString("Solution: " + std::to_string(currentSolution + 1) + "/" + std::to_string(totalSolutions));
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10); // Top left corner

    window.draw(text);
}