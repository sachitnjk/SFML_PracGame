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
    void Update(const sf::Vector2u& windowSize, float deltaTime);

    std::vector<Enemy>& GetSpawnedEnemiesRef();

    void Draw(sf::RenderWindow& window);
};

