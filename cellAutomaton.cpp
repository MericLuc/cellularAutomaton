#include "CellAutomaton.h"
#include <iostream>

/**
 * \file cellAutomaton.cpp
 * \brief Implementation of the functions defined in \a cellAutomaton.h
 * \author lhm
 */

CellAutomaton::CellAutomaton(const Config& p_config, const Application& p_app)
    :   m_pConfig   (&p_config)
    ,   m_pApplication  (&p_app)
    ,   m_cells(p_config.getSimX() * p_config.getSimY())
{
    m_random = &Random::get();
    // Creation of the cellular automaton GUI grid
    m_cellVertexPoints.reserve(p_config.getSimX() * p_config.getSimY() * 4);
    for (unsigned y = 0; y < p_config.getSimY(); ++y)
    {
        for (unsigned x = 0; x < p_config.getSimX(); ++x)
        {
            addQuad(x, y);
        }
    }

    // Random initialization of the state of each cell
    std::mt19937 rng((unsigned)std::time(nullptr));
    cellForEach([&](unsigned x, unsigned y)
    {
        unsigned index = getCellIndex(x, y);
        std::uniform_int_distribution<int> dist(0, 1);

        auto& cell = m_cells[index];
        cell = (Cell)dist(rng);
        setCellColour(x, y, cell == Cell::ON ? sf::Color::Black : m_pConfig->getFgColour());
    });
}

void CellAutomaton::render(sf::RenderWindow & p_window)
{
    p_window.draw(m_cellVertexPoints.data(), m_cellVertexPoints.size(), sf::Quads);
}

unsigned CellAutomaton::getCellIndex(const unsigned p_x, const unsigned p_y)
{
    return p_x + p_y * m_pConfig->getSimX();
}

void CellAutomaton::setCellColour(const int        p_x,
                                  const int        p_y,
                                  const sf::Color& p_colour)
{
    auto index = getCellIndex(p_x, p_y) * 4;
    for (int i = 0; i < 4; i++)
    {
        m_cellVertexPoints[index + i].color = p_colour;
    }
}

void CellAutomaton::addQuad(const unsigned p_x, const unsigned p_y)
{
    float cellSize = (float)m_pConfig->getCellSize();
    sf::Vertex topLeft;
    sf::Vertex topRight;
    sf::Vertex bottomLeft;
    sf::Vertex bottomRight;

    float pixelX = p_x * cellSize;
    float pixelY = p_y * cellSize;

    topLeft     .position = { pixelX,               pixelY };
    topRight    .position = { pixelX + cellSize,    pixelY };
    bottomLeft  .position = { pixelX,               pixelY + cellSize };
    bottomRight .position = { pixelX + cellSize,    pixelY + cellSize };

    topLeft     .color = m_pConfig->getFgColour();
    topRight    .color = m_pConfig->getFgColour();
    bottomLeft  .color = m_pConfig->getFgColour();
    bottomRight .color = m_pConfig->getFgColour();

    m_cellVertexPoints.push_back(topLeft);
    m_cellVertexPoints.push_back(bottomLeft);
    m_cellVertexPoints.push_back(bottomRight);
    m_cellVertexPoints.push_back(topRight);
}

void CellAutomaton::update()
{
    std::vector<std::pair<sf::Vector2i, Cell>> updates;
    cellForEach([&](unsigned x, unsigned y)
    {
        sf::Vector2i loc(x, y);
        unsigned count = 0;
        for (int nX = -1; nX <= 1; nX++)
        {
            for (int nY = -1; nY <= 1; nY++)
            {
                int newX = nX + x;
                int newY = nY + y;

                if (newX == -1 || newX == (int)m_pConfig->getSimX() ||
                    newY == -1 || newY == (int)m_pConfig->getSimX()||
                   (nX == 0 && nY == 0)
                   )
                {
                    continue;
                }

                auto cell = m_cells[getCellIndex(newX, newY)];
                if (cell == Cell::ON)
                    count++;
            }
        }

        int index = getCellIndex(x, y);
        auto cell = m_cells[index];
        switch (cell)
        {
            // Alive cell: Dies if (not enough) OR (too many) alive neighbors
            case Cell::ON:
                if(count < 2 || count > 3)
                {
                    updates.emplace_back(loc, Cell::OFF);
                }
                break;
            // Dead cell: Goes live if (exactly 3 neighbors) alive OR
            // get a miracle
            case Cell::OFF:
                if(count == 3)
                {
                    updates.emplace_back(loc, Cell::ON);
                }
                else
                {
                    unsigned l_rand = m_random->rand_int(0,100);

                    if(l_rand < m_pConfig->getMiracleProb())
                    {
                        updates.emplace_back(loc, Cell::ON);
                    }
                }
                break;
            default:
                break;
        }
    });

    for (auto& update : updates)
    {
        m_cells[getCellIndex(update.first.x, update.first.y)] = update.second;

        setCellColour(update.first.x,
                      update.first.y,
                      update.second == Cell::ON ? m_pConfig->getBgColour() : m_pConfig->getFgColour());
    }
}
