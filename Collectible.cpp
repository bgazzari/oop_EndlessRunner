#include "Collectible.hpp"
#include "PlayState.hpp"

Collectible::Collectible(const sf::Texture& tex, sf::Vector2f pos, float speed)
    : m_speed(speed)
{
    m_sprite.setTexture(tex);
    auto b = m_sprite.getLocalBounds();
    m_sprite.setOrigin(b.width / 2.f, b.height / 2.f);
    m_sprite.setPosition(pos);
    m_sprite.setScale(0.05f, 0.05f);

}

void Collectible::update(float dt)
{
    m_sprite.move(0.f, m_speed * dt);
    if (m_sprite.getPosition().y > 800.f)
        m_dead = true;
}

void Collectible::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Collectible::bounds() const
{
    return m_sprite.getGlobalBounds();
}

void Collectible::onPlayerCollision(PlayState& play)
{
    play.addScore(10);
    m_dead = true;
}
