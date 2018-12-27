#include "Application.h"
#include "config.h"
#include "random.h"
#include "cellAutomaton.h"

#include <iostream>
#include <fstream>
#define _WIN32_WINNT 0x0500
#include <windows.h>

/*!
 * \mainpage "Documentation of the cellular automaton"
 * This little project intends to implement <em> Jon Conway's game of life </em>. \n
 * One can find documentation about it here:
 * <ul>
 * <li> <em> https://bitstorm.org/gameoflife/ </em>
 * <li> <em> https://en.wikipedia.org/wiki/Conway's_Game_of_Life </em>
 * </ul>
 * A little modification was added to the original rules, which is that every dead cell has a chance
 * of miraculously turning alive. This can of course be disabled by setting that chance to 0.
 * \author lhm
 */

 /*!
 * \file main.cpp
 * \brief main file
 * \author lhm
 */

namespace
{
    void setConsolePosition()
    {
        HWND consoleWindow = GetConsoleWindow();
        SetWindowPos(consoleWindow, 0, 0, 0, 500, 500, SWP_NOSIZE | SWP_NOZORDER);
    }

    template<typename T>
    void run(const Config& p_conf)
    {
        std::cout << "Controls: \n";
        std::cout << "Up - Zoom in\nDown - Zoom out\nZQSD - Move Around\n";
        std::cout << "R - Reset the view\n";
        std::cin.ignore();

        Application app(p_conf);
        app.init<T>();
        app.run();

        std::cout << '\n';
    }
}

int main()
{
    setConsolePosition();
    Config conf;
    conf.loadConfig();
    run<CellAutomaton>(conf);
}
