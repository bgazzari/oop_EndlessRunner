#include "GameOverState.hpp"
#include "MenuState.hpp"
#include "PlayState.hpp"
#include "Game.hpp"
#include <iostream>

static void centerTextX(sf::Text& text, float y)
{
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, 0.f);
    text.setPosition(640.f, y);
}

GameOverState::GameOverState(int score)
    : m_score(score)
{
    m_textures.load("background", "assets/textures/menu_bg.png");
    m_bg.setTexture(m_textures.get("background"));

    auto b = m_bg.getLocalBounds();
    m_bg.setScale(1280.f / b.width, 720.f / b.height);

    m_titleFont.loadFromFile("assets/fonts/milkyway.ttf");
    m_numFont.loadFromFile("assets/fonts/consola.ttf");

    m_titleText.setFont(m_titleFont);
    m_titleText.setString("GAME OVER");
    m_titleText.setCharacterSize(90);
    m_titleText.setFillColor(sf::Color(40, 60, 90));
    m_titleText.setOutlineColor(sf::Color(240, 240, 240));
    m_titleText.setOutlineThickness(3.f);

    centerTextX(m_titleText, 100.f);

    m_scoreLabel.setFont(m_titleFont);
    m_scoreLabel.setString("Score:");
    m_scoreLabel.setCharacterSize(36);
    m_scoreLabel.setFillColor(sf::Color(40, 60, 90));
    m_scoreLabel.setOutlineColor(sf::Color(240, 240, 240));
    m_scoreLabel.setOutlineThickness(2.f);
    m_scoreLabel.setPosition(550.f, 250.f);

    m_scoreValue.setFont(m_numFont);
    m_scoreValue.setString(std::to_string(m_score));
    m_scoreValue.setCharacterSize(36);
    m_scoreValue.setFillColor(sf::Color(40, 60, 90));
    m_scoreValue.setOutlineColor(sf::Color(240, 240, 240));
    m_scoreValue.setOutlineThickness(2.f);
    m_scoreValue.setPosition(680.f, 250.f);

    m_hintText.setFont(m_titleFont);
    m_hintText.setString("Press Enter to Retry\nESC to return to Menu");
    m_hintText.setCharacterSize(28);
    m_hintText.setFillColor(sf::Color(40, 60, 90));
    m_hintText.setOutlineColor(sf::Color(240, 240, 240));
    m_hintText.setOutlineThickness(2.f);

    centerTextX(m_hintText, 350.f);
}


void GameOverState::handleEvent(Game& game, const sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Enter) {
            game.changeState(std::make_unique<PlayState>());
        }
        if (e.key.code == sf::Keyboard::Escape) {
            game.changeState(std::make_unique<MenuState>());
        }
    }

}

void GameOverState::update(Game&, float) {}

void GameOverState::draw(Game&, sf::RenderWindow& window)
{
    window.draw(m_bg);
    window.draw(m_titleText);
    window.draw(m_scoreLabel);
    window.draw(m_scoreValue);
    window.draw(m_hintText);
}
