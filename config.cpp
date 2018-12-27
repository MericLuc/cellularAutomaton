#include "config.h"
#include <iostream>
#include <fstream>

/**
 * \file config.cpp
 * \brief Implementation of the functions defined in \a config.h
 * \author lhm
 */


void Config::init()
{
    windowSize.x -= windowSize.x % cellSize;
    windowSize.y -= windowSize.y % cellSize;

    simSize.x = windowSize.x / cellSize;
    simSize.y = windowSize.y / cellSize;
}

void Config::loadConfig()
{
    std::ifstream inFile("config.txt");
    if (!inFile.is_open())
    {
        std::cout << "Unable to load config, making default settings\n";
        setFrameRate(15);
        setSimX(1280);
        setSimY(720);
        setCellSize(2);
        setMiracleProb(5);

        return;
    }

    std::string line;
    unsigned tmp;
    while (std::getline(inFile, line))
    {
        if (line == "winx")
        {
            inFile >> tmp;
            setWindowSizeX(tmp);
        }
        else if (line == "winy")
        {
            inFile >> tmp;
            setWindowSizeY(tmp);
        }
        else if (line == "cellsize")
        {
            inFile >> tmp;
            setCellSize(tmp);
        }
        else if (line == "bgcol")
        {
            unsigned r, g, b;
            sf::Color l_color;

            inFile >> r;
            inFile >> g;
            inFile >> b;

            l_color = sf::Color(r, g, b);
            setBgColour(l_color);
        }
        else if (line == "fgcol")
        {
            unsigned r, g, b;
            sf::Color l_color;
            inFile >> r;
            inFile >> g;
            inFile >> b;

            l_color = sf::Color(r, g, b);
            setFgColour(l_color);
        }
        else if (line == "miracleProb")
        {
            inFile >> tmp;
            setMiracleProb(tmp);
        }
    }
    init();
}
