#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include "CellAutomaton.h"

/*!
 * \file application.h
 * \brief Definition of the \a Application class containing every other elements of the simulation.
 * \author lhm
 */

/*!
 * \class Keyboard
 * \brief This class contains the states of the different keys of the keyboard.
 */
class Keyboard
{
    public:
        /*!
         * Constructor
         */
        Keyboard();

        /*!
         * \function update
         * \brief Updates the state of the keyboard when a new event occurs.
         * \param p_event The event that occured.
         */
        void update(sf::Event p_event);

        /*!
         * \funciton isKeyDown
         * \brief Returns the state (pressed or not) of the requested key.
         * \param p_key the requested key
         * \return true if \a key is pressed, false otherwise.
         */
        bool isKeyDown(sf::Keyboard::Key p_key) const;

    private:
        std::array<bool, sf::Keyboard::KeyCount> m_keys; /*!< Pair of (state,Keys) of the keyboard */
};

class Config;

/*!
 * \lass Application
 * \brief Mother class containing and running the simulation:
 * <ul>
 * <li> The window of simulation
 * <li> The keyboard
 * <li> The view associated to the window
 * <li> The cellular automaton
 * </ul>
 */
class Application
{
    public:
        Application(const Config& config);

        template<typename T>
        void init()
        {
            m_automaton = std::make_unique<T>(*m_pConfig, *this);
        }

        void run();

        const sf::RenderWindow& getWindow() const;

    private:
        void pollEvents();
        void input  (float dt);
        void render ();

        /*!
         * Resets the view to initial state (center, no zoom)
         */
        void resetView();

        std::unique_ptr<CellAutomaton> m_automaton; /*!< Cellular automaton */
        const Config* m_pConfig = nullptr;          /*!< Configuration of the simulation */
        sf::RenderWindow m_window;                  /*!< Simulation window */
        Keyboard         m_keyboard;                /*!< Keyboard */
        sf::View         m_view;                    /*!< Simulation view */
        bool dragged;                               /*!< true if mouse currently dragged */
        float m_zoom = 1;                           /*!< zoom factor */

};

#endif // APPLICATION_H
