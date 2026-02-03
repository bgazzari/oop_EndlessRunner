#pragma once
#include "Entity.hpp"

class Obstacle : public Entity {
public:
    Obstacle(const sf::Texture& tex, sf::Vector2f pos, float speed, int lane);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect bounds() const override;
    void onPlayerCollision(PlayState& play) override;

    int getLane() const { return m_lane; }
    float getY() const { return m_sprite.getPosition().y; }

private:
    sf::Sprite m_sprite;
    float m_speed;
    int m_lane;
};
