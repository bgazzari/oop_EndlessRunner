#pragma once
#include "GameState.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>

class GameOverState : public GameState {
public:
    GameOverState(int score);

    void handleEvent(Game& game, const sf::Event& e) override;
    void update(Game& game, float dt) override;
    void draw(Game& game, sf::RenderWindow& window) override;

private:
    
    TextureManager m_textures;
    sf::Sprite m_bg;

    sf::Font m_titleFont;
    sf::Font m_numFont;

    sf::Text m_titleText;
    sf::Text m_scoreLabel;
    sf::Text m_scoreValue;
    sf::Text m_hintText;

    int m_score = 0;

};
