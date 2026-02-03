#include "Game.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"

Game::Game()
    : m_window(sf::VideoMode(1280, 720), "Endless Runner")
{
    m_window.setFramerateLimit(60);
    changeState(std::make_unique<MenuState>());
   

}

Game::~Game() = default;

void Game::changeState(std::unique_ptr<GameState> state)
{
    m_state = std::move(state);
}

void Game::run()
{
    while (m_window.isOpen()) {
        float dt = m_clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            m_window.close();
        if (m_state)
            m_state->handleEvent(*this, e);
    }
}

void Game::update(float dt)
{
    if (m_state)
        m_state->update(*this, dt);
}

void Game::render()
{
    m_window.clear();
    if (m_state)
        m_state->draw(*this, m_window);
    m_window.display();
}
