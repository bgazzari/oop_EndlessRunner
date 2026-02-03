#pragma once
#include "Entity.hpp"

class Player : public Entity {
public:
    Player(const sf::Texture& tex);

    void moveLane(int dir);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect bounds() const override;
    void onPlayerCollision(PlayState&) override {}
    bool inGrace() const { return m_laneGrace > 0.f; }


private:
    sf::Sprite m_sprite;
    int m_lane = 1;

    float m_laneGrace = 0.f;


};
