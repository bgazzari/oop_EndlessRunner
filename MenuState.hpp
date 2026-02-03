#pragma once
#include "GameState.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public GameState {
public:
    MenuState();

    void handleEvent(Game& game, const sf::Event& e) override;
    void update(Game& game, float dt) override;
    void draw(Game& game, sf::RenderWindow& window) override;

private:
   
    sf::Sprite m_bg;

    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_hint;

    TextureManager m_textures;

};
