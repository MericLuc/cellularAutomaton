#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "config.h"
#include "random.h"

/**
 * \file cellAutomaton.h
 * \brief Definition of the cellular automaton class used for the "Game of life"
 * \author lhm
 */

class Application;

/*!
 * \enum Cell
 * \brief Enumerate containing the possible states of a cell (dead or alive).
 */
enum Cell
{
    ON,
    OFF
};

/*!
 * \class CellAutomaton
 * \brief Cellular automaton containing the rules of the simulation.
 */
class CellAutomaton
{
    public:
        /*!
         * \function CellAutomaton
         * \brief Creates a cellular automaton for the "Game of life".
         * \param p_config The GUI configuration of the automaton.
         * \param p_app The application
         */
        CellAutomaton(const Config& p_config, const Application& p_app);

        /*!
         * Default destructor
         */
        ~CellAutomaton() = default;

        /*!
         * \function input
         * \brief Called when a SFML event occurs ( see \a sf::Event ).
         * \param p_event the event
         */
        void input(const sf::Event& p_event){};

        /*!
         * \function update
         * \brief Called to get the next cellular automaton state
         * \author lhm
         */
        void update();

        /*!
         * \function render
         * \brief Displays the application to the window.
         * \param p_window the window
         */
        void render(sf::RenderWindow& p_window);

    protected:

        /*!
         * \function getCellIndex
         * \brief Returns the 1D index of the cell at specified 2D indexes.
         * \param p_x the requested abscissa
         * \param p_y the requested ordinate
         * \return the requested index.
         */
        unsigned getCellIndex(const unsigned p_x, const unsigned p_y);

        /*!
         * \function setCellColour
         * \brief Set a colour to the requested cell.
         * \param p_x the requested abscissa
         * \param p_y the requested ordinate
         * \param p_colour the requested colour.
         */
        void setCellColour(const int p_x, const int p_y, const sf::Color& p_colour);

        /*!
         * \function addQuad
         * \brief Creates a quad at the requested indexes.
         * \param p_x the requested abscissa
         * \param p_y the requested ordinate
         */
        void addQuad(const unsigned p_x, const unsigned p_y);

        template<typename Func>
        void cellForEach(Func function);

    private:
        const Application* const m_pApplication;        /**< application associated to the cellular automaton */
        const Config* const m_pConfig;                  /**< configuration associated to the cellular automaton */
        std::vector<sf::Vertex> m_cellVertexPoints;     /**< vector containing the cells of the cellular automaton */
        std::vector<Cell> m_cells;                      /**< vector containing the cells of the cellular automaton */
        Random*     m_random;                           /**< Random numbers generator */
};

template<typename Func>
void CellAutomaton::cellForEach(Func function)
{
    for (unsigned y = 0; y < m_pConfig->getSimY(); ++y)
    {
        for (unsigned x = 0; x < m_pConfig->getSimX(); ++x)
        {
            function(x, y);
        }
    }
}
