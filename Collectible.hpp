#pragma once
#include "Entity.hpp"

class Collectible : public Entity {
public:
    Collectible(const sf::Texture& tex, sf::Vector2f pos, float speed);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect bounds() const override;
    void onPlayerCollision(PlayState& play) override;

private:
    sf::Sprite m_sprite;
    float m_speed;
};
