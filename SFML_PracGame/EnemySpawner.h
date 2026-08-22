#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "Player.h"

class EnemySpawner
{
private:
    std::vector<Enemy> enemies;

    int maxEnemySpawn = 6;

    float spawnInterval = 0.8f;
    float spawnTimer = 0.0f;

public:
    void SpawnEnemy(const sf::Vector2u& windowSize);
    void Update(sf::Vector2f playerPosition, const sf::Vector2u& windowSize, float deltaTime);

    void CheckPlayerAttack(const Player& player);

    void Draw(sf::RenderWindow& window);
};

