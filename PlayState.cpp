#include "PlayState.hpp"
#include "GameOverState.hpp"
#include "Game.hpp"
#include "Obstacle.hpp"
#include "Collectible.hpp"
#include "Constants.hpp"
#include <cstdlib>
#include <iostream>

static void shuffle3(int a[3]) {
    for (int i = 2; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(a[i], a[j]);
    }
}


PlayState::PlayState()
{
    m_textures.load("player", "assets/textures/player.png");
    m_textures.load("obstacle", "assets/textures/obstacle.png");
    m_textures.load("collectible", "assets/textures/collectible.png");
    m_hasBg = m_textures.load("background", "assets/textures/background.png");
    if (m_hasBg) {
        const auto& tex = m_textures.get("background");

        m_bg1.setTexture(tex);
        m_bg2.setTexture(tex);

        auto b = m_bg1.getLocalBounds();
        float scaleX = 1280.f / b.width;
        float scaleY = 720.f / b.height;

        m_bg1.setScale(scaleX, scaleY);
        m_bg2.setScale(scaleX, scaleY);

        m_bg1.setPosition(0.f, 0.f);
        m_bg2.setPosition(0.f, -720.f);
    }


    m_player = std::make_unique<Player>(m_textures.get("player"));

    m_font.loadFromFile("assets/fonts/milkyway.ttf");
    m_scoreLabel.setFont(m_font);
    m_scoreLabel.setString("Score:");
    m_scoreLabel.setCharacterSize(28);
    m_scoreLabel.setOutlineThickness(2.f);
    m_scoreLabel.setOutlineColor(sf::Color::Black);
    m_scoreLabel.setFillColor(sf::Color::White);
    m_scoreLabel.setPosition(20.f, 12.f);

    m_numFont.loadFromFile("assets/fonts/consola.ttf");
    m_scoreValue.setFont(m_numFont);
    m_scoreValue.setCharacterSize(28);
    m_scoreValue.setOutlineThickness(2.f);
    m_scoreValue.setOutlineColor(sf::Color::Black);
    m_scoreValue.setFillColor(sf::Color::White);
    m_scoreValue.setPosition(140.f, 12.f);



    m_hasHeart = m_textures.load("heart", "assets/textures/heart.png");
    if (m_hasHeart) {
        m_heart.setTexture(m_textures.get("heart"));
        auto hb = m_heart.getLocalBounds();
        m_heart.setOrigin(hb.width / 2.f, hb.height / 2.f);

        float targetW = 28.f;
        float s = targetW / hb.width;
        m_heart.setScale(s, s);
    }


}




void PlayState::handleEvent(Game& game, const sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Left)  m_player->moveLane(-1);
        if (e.key.code == sf::Keyboard::Right) m_player->moveLane(1);
    }
}



bool PlayState::laneHasObstacle(int lane) const
{
    for (const auto& e : m_entities) {
        auto* obs = dynamic_cast<Obstacle*>(e.get());
        if (!obs) continue;

        if (obs->getLane() == lane && obs->getY() < Const::PlayerY - 40.f) {
            return true;
        }

    }
    return false;
}



void PlayState::loseLife()
{
    if (m_hitCooldown > 0.f) return;

    m_lives--;
    m_hitCooldown = m_hitCooldownTime;

    if (m_lives <= 0) {
        m_gameOver = true;
    }
}




void PlayState::update(Game& game, float dt)
{
    if (m_gameOver) {
        game.changeState(std::make_unique<GameOverState>(m_score));
        return;
    }

    if (m_hitCooldown > 0.f) m_hitCooldown -= dt;

    m_timeAlive += dt;

    m_speedMult = 1.f + 0.03f * m_timeAlive;
    if (m_speedMult > m_speedMultMax) m_speedMult = m_speedMultMax;

    float spawnMult = 1.f / m_speedMult;
    if (spawnMult < m_spawnMultMin) spawnMult = m_spawnMultMin;

    if (m_hasBg) {
        float scroll = m_bgScrollSpeed * m_speedMult;

        m_bg1.move(0.f, scroll * dt);
        m_bg2.move(0.f, scroll * dt);

        if (m_bg1.getPosition().y >= 720.f) {
            m_bg1.setPosition(0.f, m_bg2.getPosition().y - 720.f);
        }
        if (m_bg2.getPosition().y >= 720.f) {
            m_bg2.setPosition(0.f, m_bg1.getPosition().y - 720.f);
        }
    }


    m_spawnTimer += dt;
    m_collectibleTimer += dt;


    float obstacleInterval = 1.8f * spawnMult;
    if (m_spawnTimer > obstacleInterval){

        if (m_bagIndex == 0) shuffle3(m_laneBag);

        int lane = m_laneBag[m_bagIndex];
        m_bagIndex = (m_bagIndex + 1) % 3;

        if (lane == m_lastLane) {
            lane = m_laneBag[m_bagIndex];
            m_bagIndex = (m_bagIndex + 1) % 3;
        }

        m_lastLane = lane;
        m_lastObstacleLane = lane;

        m_entities.push_back(std::make_unique<Obstacle>(m_textures.get("obstacle"),
                Const::SpawnLanes[lane],300.f * m_speedMult, lane));

        m_spawnTimer = 0.f;
    }

    
    float coinInterval = m_collectibleInterval * spawnMult;
    if (m_collectibleTimer > coinInterval){

        int candidateLanes[3] = { 0, 1, 2 };
        shuffle3(candidateLanes);

        int chosenLane = -1;
        for (int i = 0; i < 3; i++) {
            int lane = candidateLanes[i];
            if (!laneHasObstacle(lane)) {
                chosenLane = lane;
                break;
            }
        }

        if (chosenLane != -1) {
            m_entities.push_back(
                std::make_unique<Collectible>(m_textures.get("collectible"),
                    Const::SpawnLanes[chosenLane],240.f * m_speedMult));
        }

        m_collectibleTimer = 0.f;
    }


    m_player->update(dt);

    for (auto& e : m_entities)
        e->update(dt);

    for (auto& e : m_entities) {
        if (!e->dead() && !m_player->inGrace() &&
            e->bounds().intersects(m_player->bounds()))
        {
            e->onPlayerCollision(*this);
        }
    }

    m_entities.erase(
        std::remove_if(m_entities.begin(), m_entities.end(),
            [](auto& e) { return e->dead(); }),
        m_entities.end()
    );

    m_scoreValue.setString(std::to_string(m_score));

}




void PlayState::draw(Game&, sf::RenderWindow& window)
{
    if (m_hasBg) {
        window.draw(m_bg1);
        window.draw(m_bg2);
    }

    if (m_hasHeart) {
        for (int i = 0; i < m_lives; i++) {
            m_heart.setPosition(30.f + i * 36.f, 60.f);
            window.draw(m_heart);
        }
    }

    m_player->draw(window);
    for (auto& e : m_entities) e->draw(window);

    window.draw(m_scoreLabel);
    window.draw(m_scoreValue);

}
