#include "Player.hpp"
#include "Constants.hpp"
#include <algorithm>

static sf::FloatRect shrinkRect(sf::FloatRect r, float px)
{
    r.left += px;
    r.top += px;
    r.width -= 2.f * px;
    r.height -= 2.f * px;
    return r;
}

Player::Player(const sf::Texture& tex)
{
    m_sprite.setTexture(tex);
    auto b = m_sprite.getLocalBounds();
    m_sprite.setOrigin(b.width / 2.f, b.height / 2.f);
    m_sprite.setPosition(Const::Lanes[m_lane]);
}

void Player::moveLane(int dir)
{
    m_lane = std::clamp(m_lane + dir, 0, 2);
    m_sprite.setPosition(Const::Lanes[m_lane]);
    m_laneGrace = 0.15f;

}

void Player::update(float dt)
{
    if (m_laneGrace > 0.f) m_laneGrace -= dt;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Player::bounds() const
{
    auto r = m_sprite.getGlobalBounds();

    const float shrinkX = r.width * 0.28f;
    const float shrinkY = r.height * 0.20f;

    r.left += shrinkX;
    r.width -= 2.f * shrinkX;
    r.top += shrinkY;
    r.height -= 2.f * shrinkY;

    return r;
}


