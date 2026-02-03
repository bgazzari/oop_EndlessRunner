#pragma once
#include <SFML/Graphics.hpp>

class PlayState;

class Entity {
public:
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect bounds() const = 0;
    virtual void onPlayerCollision(PlayState& play) = 0;

    bool dead() const { return m_dead; }
    void kill() { m_dead = true; }

protected:
    bool m_dead = false;
};
