#ifndef CONFIG_H
#define CONFIG_H

/**
 * \file config.h
 * \brief Configuration of the cellular automaton (window size, cells size...).
 * Contains every customizable features of the simulation (window size, cells size, framerate...)
 * \author lhm
 */

#include <SFML/Graphics.hpp>
#include <iostream>

/*!
 * \class Config
 * \brief Configuration class containing customized elements of the simulation.
 */
class Config
{
    public:
        Config() = default;

        /*!
         * \function Config
         * \brief Creates a \a Config object.
         * \param p_winSize Dimensions of the window
         * \param p_cellSize size of a cell (a cell is of dimensions <em> (p_cellSize x p_cellSize) </em>)
         */
        Config(const sf::Vector2u& p_winSize, unsigned p_cellSize)
            : windowSize    (p_winSize)
            ,   cellSize    (p_cellSize)
        {
            init();
        }

        /*!
         * Get the simulation abscissa
         */
        const unsigned& getSimX() const { return simSize.x; }

        /*!
         * Get the simulation ordinate
         */
        const unsigned& getSimY() const { return simSize.y; }

        /*!
         * Get the foreground colour
         */
        const sf::Color& getFgColour() const { return fgColour; }

        /*!
         * Get the background colour
         */
        const sf::Color& getBgColour() const { return bgColour; }

        /*!
         * Get the window x size
         */
        const unsigned& getWindowSizeX() const { return windowSize.x; }

        /*!
         * Get the window y size
         */
        const unsigned& getWindowSizeY() const { return windowSize.y; }

        /*!
         * Get the size of cells
         */
        const unsigned& getCellSize() const { return cellSize; }

        /*!
         * Get the framerate of the simulation
         */
         const unsigned& getFrameRate() const { return frameRate; }

        /*!
         * Get the probability of cell "miracle" apparition
         */
         const unsigned& getMiracleProb() const { return miracle_prob; }

        /*!
         * Set the simulation abscissa
         */
        void setSimX(const unsigned p_x) { simSize.x = p_x; }

        /*!
         * Set the simulation ordinate
         */
        void setSimY(const unsigned p_y) { simSize.y = p_y; }

        /*!
         * Set the foreground colour
         */
        void setFgColour(const sf::Color& p_colour) { fgColour = p_colour; }

        /*!
         * Set the background colour
         */
        void setBgColour(const sf::Color& p_colour) { bgColour = p_colour; }

        /*!
         * Set the window x size
         */
        void setWindowSizeX(const unsigned p_x) { windowSize.x = p_x; }

        /*!
         * Set the window y size
         */
        void setWindowSizeY(const unsigned p_y) { windowSize.y = p_y; }

        /*!
         * Set the size of cells
         */
        void setCellSize(const unsigned p_size) { cellSize = p_size; }

        /*!
         * Set the framerate of the simulation
         */
         void setFrameRate(const unsigned& p_frameRate) { frameRate = p_frameRate; }

        /*!
         * Set the probability of cell "miracle" apparition
         */
         void setMiracleProb(const unsigned& p_miracleProb) { miracle_prob = p_miracleProb; }

        /*!
         * \function init
         * \brief performs the initialization step of a \a Config object.
         */
        void init();

        /*!
         * \function loadConfig
         * \brief load configuration parameters from <em>"config.txt"</em> file.
         */
        void loadConfig();

    private:
        sf::Vector2u windowSize = { 1280, 720 };        /**< Dimensions of the display window */
        sf::Vector2u simSize;                           /**< Size of the simulation */
        unsigned cellSize = 4;                          /**< Size of a cell */
        unsigned frameRate = 15;                        /**< Maximum framerate for the simulation */

        sf::Color bgColour = { 150, 150, 150 };         /**< Default background colour */
        sf::Color fgColour = { 25, 25, 25 };            /**< Default foreground colour */

        unsigned miracle_prob = 5;                      /**< Probability a cell appears for no apparent reason */
};

#endif // CONFIG_H
