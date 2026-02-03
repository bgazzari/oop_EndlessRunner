#include "MenuState.hpp"
#include "PlayState.hpp"
#include "Game.hpp"
#include <iostream>
#include <filesystem>

static void centerText(sf::Text& text, float x, float y)
{
    auto b = text.getLocalBounds();
    text.setOrigin(
        b.left + b.width / 2.f,
        b.top + b.height / 2.f
    );
    text.setPosition(x, y);
}


MenuState::MenuState()
{
    m_textures.load("menu_bg", "assets/textures/menu_bg.png");
    m_bg.setTexture(m_textures.get("menu_bg"));
    auto b = m_bg.getLocalBounds();
    m_bg.setScale(1280.f / b.width, 720.f / b.height);
    m_bg.setPosition(0.f, 0.f);

    m_font.loadFromFile("assets/fonts/milkyway.ttf");

    m_title.setFont(m_font);
    m_title.setString("ENDLESS RUNNER");
    m_title.setCharacterSize(72);
    m_title.setFillColor(sf::Color(40, 60, 90));
    m_title.setOutlineThickness(3.f);
    m_title.setOutlineColor(sf::Color(240, 240, 240));
    m_title.setLetterSpacing(1.1f);
    centerText(m_title, 640.f, 220.f);

    m_hint.setFont(m_font);
    m_hint.setString("ENTER to Play\nESC to Exit");
    m_hint.setCharacterSize(32);
    m_hint.setFillColor(sf::Color(60, 60, 60));
    m_hint.setOutlineThickness(2.f);
    m_hint.setOutlineColor(sf::Color(230, 230, 230));
    m_hint.setLetterSpacing(1.05f);
    centerText(m_hint, 640.f, 360.f);


}

void MenuState::handleEvent(Game& game, const sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Enter)
            game.changeState(std::make_unique<PlayState>());
        if (e.key.code == sf::Keyboard::Escape)
            game.window().close();
    }
}

void MenuState::update(Game&, float) {}

void MenuState::draw(Game&, sf::RenderWindow& window)
{
    window.draw(m_bg);
    window.draw(m_title);
    window.draw(m_hint);

}
