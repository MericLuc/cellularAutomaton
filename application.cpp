#include "application.h"

#include <iostream>
#include <ctime>
#include <thread>

#include "random.h"
#include "config.h"

/*!
 * \file application.cpp
 * \brief Implementation of the functions defined in \a application.h
 * \author lhm
 */

Keyboard::Keyboard()
{
    std::fill(m_keys.begin(), m_keys.end(), false);
}

void Keyboard::update(sf::Event p_event)
{
    switch (p_event.type)
    {
        case sf::Event::KeyPressed:
            m_keys[p_event.key.code] = true;
            break;

        case sf::Event::KeyReleased:
            m_keys[p_event.key.code] = false;
            break;

        default:
            break;
    }
}

bool Keyboard::isKeyDown(sf::Keyboard::Key p_key) const
{
    return m_keys.at(p_key);
}

Application::Application(const Config& config)
    : m_window({ config.getWindowSizeX(), config.getWindowSizeY()}, "Cellular Automaton - Game of life")
    , m_pConfig(&config)
{
    resetView();
    dragged = false;
    m_window.setFramerateLimit(config.getFrameRate());
}

void Application::run()
{
    sf::Clock deltaClock;
    m_window.setKeyRepeatEnabled(false);

    while (m_window.isOpen())
    {
        input (deltaClock.restart().asSeconds());
        m_automaton->update();

        render  ();
        pollEvents();
    }
}

const sf::RenderWindow& Application::getWindow() const
{
    return m_window;
}

void Application::pollEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e))
    {
        m_automaton->input(const_cast<const sf::Event&>(e));
        m_keyboard.update(e);
        switch (e.type)
        {
            case sf::Event::MouseWheelMoved:
                m_view.zoom(1 - e.mouseWheel.delta/8.0);
                break;
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                dragged = true;
                break;
            case sf::Event::MouseButtonReleased:
                dragged = false;
                break;
            case sf::Event::MouseMoved:
                if(dragged)
                {
                    //std::cout<< "*";
                }
                break;
        }
    }
}

void Application::input(float dt)
{
    float speed = 250;
    sf::Vector2f change;

    if (m_keyboard.isKeyDown(sf::Keyboard::Z))
    {
        change.y -= speed;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::S))
    {
        change.y += speed;
    }

    if (m_keyboard.isKeyDown(sf::Keyboard::Q))
    {
        change.x -= speed;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::D))
    {
        change.x += speed;
    }

    if (m_keyboard.isKeyDown(sf::Keyboard::Up))
    {
        m_view.zoom(0.95f);
    }

    if (m_keyboard.isKeyDown(sf::Keyboard::Down))
    {
        m_view.zoom(1.05f);
    }

    if (m_keyboard.isKeyDown(sf::Keyboard::R))
    {
        resetView();
    }

    m_view.move(change * dt);
}

void Application::render()
{
    m_window.setView(m_view);
    m_window.clear(m_pConfig->getBgColour());

    //Pixels
    m_window.setView(m_view);
    m_automaton->render(m_window);

    //GUI
    m_window.setView(m_window.getDefaultView());

    m_window.display();
}

void Application::resetView()
{
    m_view = sf::View();
    m_view.setCenter({ (float)m_pConfig->getWindowSizeX() / 2,  (float)m_pConfig->getWindowSizeY() / 2 });
    m_view.setSize({ (float)m_pConfig->getWindowSizeX(),        (float)m_pConfig->getWindowSizeY() });
}
