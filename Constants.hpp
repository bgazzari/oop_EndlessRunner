#pragma once
#include <SFML/System/Vector2.hpp>

namespace Const {
    constexpr float PlayerY = 550.f;

    static const sf::Vector2f Lanes[3] = {
        {213.f, PlayerY},
        {637.f, PlayerY},
        {1064.f, PlayerY}
    };

    static const sf::Vector2f SpawnLanes[3] = {
        {213.f, -120.f},
        {637.f, -120.f},
        {1064.f, -120.f}
    };
}
