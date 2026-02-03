#pragma once
#include "GameState.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include <memory>
#include <vector>

class PlayState : public GameState {
public:
    PlayState();

    void handleEvent(Game& game, const sf::Event& e) override;
    void update(Game& game, float dt) override;
    void draw(Game& game, sf::RenderWindow& window) override;

    void addScore(int s) { m_score += s; }
    void gameOver() { m_gameOver = true; }
    void loseLife();
   

private:

    bool laneHasObstacle(int lane) const;

    TextureManager m_textures;
    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<Entity>> m_entities;

    float m_spawnTimer = 0.f;
    int m_score = 0;
    bool m_gameOver = false;

    float m_collectibleTimer = 0.f;
    float m_collectibleInterval = 1.2f;

    sf::Font m_font;
    sf::Font m_numFont;

    sf::Sprite m_bg1, m_bg2;
    float m_bgOffset = 0.f;
    float m_bgScrollSpeed = 180.f;
    bool m_hasBg = false;

    int m_lastLane = -1;
    int m_lastObstacleLane = -1;
    int m_laneBag[3] = { 0,1,2 };
    int m_bagIndex = 0;


    int m_lives = 3;

    sf::Sprite m_heart;
    bool m_hasHeart = false;

    float m_hitCooldown = 0.f;
    float m_hitCooldownTime = 0.6f;

    sf::Text m_scoreLabel;
    sf::Text m_scoreValue;

    float m_timeAlive = 0.f;
    float m_speedMult = 1.f;
    float m_speedMultMax = 2.2f;
    float m_spawnMultMin = 0.55f;


};
