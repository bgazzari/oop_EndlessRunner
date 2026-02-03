#include "Obstacle.hpp"
#include "PlayState.hpp"

static sf::FloatRect shrinkRect(sf::FloatRect r, float px)
{
    r.left += px;
    r.top += px;
    r.width -= 2.f * px;
    r.height -= 2.f * px;
    return r;
}

Obstacle::Obstacle(const sf::Texture& tex, sf::Vector2f pos, float speed, int lane)
    : m_speed(speed), m_lane(lane)
{
    m_sprite.setTexture(tex);
    auto b = m_sprite.getLocalBounds();
    m_sprite.setOrigin(b.width / 2.f, b.height / 2.f);
    m_sprite.setPosition(pos);
    m_sprite.setScale(0.4f, 0.4f);
}

void Obstacle::update(float dt)
{
    m_sprite.move(0.f, m_speed * dt);
    if (m_sprite.getPosition().y > 800.f)
        m_dead = true;
}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Obstacle::bounds() const
{
    auto r = m_sprite.getGlobalBounds();

    const float shrinkX = r.width * 0.18f;
    const float shrinkY = r.height * 0.12f;

    r.left += shrinkX;
    r.width -= 2.f * shrinkX;
    r.top += shrinkY;
    r.height -= 2.f * shrinkY;

    return r;
}

void Obstacle::onPlayerCollision(PlayState& play)
{
    play.loseLife();
    m_dead = true;
}
