//
// Created by Dave Smith on 2/23/21.
//

#include "Fonts.h"
std::vector<sf::Font> Fonts::fonts(Fonts::FONT_COUNT, sf::Font());
std::vector<bool> Fonts::loadedFonts(Fonts::FONT_COUNT, false);


sf::Font& Fonts::getFont(Styles fontStyle)
{
    loadFont(fontStyle);
    return fonts[fontStyle];
}

void Fonts::loadFonts() {

    loadFont(OPEN_SANS_BOLD, "fonts/OpenSans-Bold.ttf");
}

void Fonts::loadFont(Styles fontStyle, std::string filepath)
{

    if(!loadedFonts[fontStyle])
    {
        if(!fonts[fontStyle].loadFromFile(filepath))
        {
            loadedFonts[fontStyle] = true;
        }
    }
}

std::string Fonts::getFontPath(Fonts::Styles fontStyle)
{
    switch(fontStyle)
    {
        case OPEN_SANS_BOLD: return "fonts/OpenSans-Bold.ttf";
        case AGENT: return "fonts/Agent.ttf";
        case ARCADE: return "fonts/Arcade.ttf";
        case ARIAL: return "fonts/arial.ttf";
    }
}

void Fonts::loadFont(Fonts::Styles fontStyle)
{
    loadFont(fontStyle, getFontPath(fontStyle));
}
