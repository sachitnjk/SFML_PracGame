#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "EnemySpawner.h"

class EnemyManager
{
public:
	EnemyManager(EnemySpawner& enemySpawner);

	void Update(sf::Vector2f playerPosition, float deltaTime);

private:

	EnemySpawner& enemySpawnerRef;

};

