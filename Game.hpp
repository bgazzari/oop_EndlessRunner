#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameState;

class Game {
public:
    Game();
    ~Game();

    void run();
    void changeState(std::unique_ptr<GameState> state);
    sf::RenderWindow& window() { return m_window; }

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow m_window;
    std::unique_ptr<GameState> m_state;
    sf::Clock m_clock;
};
