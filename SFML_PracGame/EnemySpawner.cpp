#include "EnemySpawner.h"
#include <random>

void EnemySpawner::SpawnEnemy(const sf::Vector2u& windowSize)
{
	static std::random_device randomDevice;
	static std::mt19937 randomGenerator(randomDevice());

	std::uniform_int_distribution<int> edgeDistribution(0, 3);
	std::uniform_real_distribution<float> xDistribution(0.0f, static_cast<float>(windowSize.x));
	std::uniform_real_distribution<float> yDistribution(0.0f, static_cast<float>(windowSize.y));

	sf::Vector2f spawnPosition;

	int edge = edgeDistribution(randomGenerator);

	switch (edge)
	{
	case 0:
		spawnPosition = { xDistribution(randomGenerator), -40.0f };
		break;
	case 1:
		spawnPosition = {static_cast<float>(windowSize.x) + 40.0f, yDistribution(randomGenerator)};
		break;
	case 2:
		spawnPosition = {xDistribution(randomGenerator), static_cast<float>(windowSize.y) + 40.0f};
		break;
	case 3:
		spawnPosition = {-40.0f, yDistribution(randomGenerator)};
		break;
	}

	Enemy enemy;
	enemy.Initialize(spawnPosition);
	enemies.push_back(enemy);
}

void EnemySpawner::Update(const sf::Vector2u& windowSize, float deltaTime)
{
	//---Auto spawn 
	spawnTimer += deltaTime;
	if (spawnTimer >= spawnInterval && enemies.size() < maxEnemySpawn)
	{
		SpawnEnemy(windowSize);

		spawnTimer = 0.0f;
	}
}

std::vector<Enemy>& EnemySpawner::GetSpawnedEnemiesRef()
{
	return enemies;
}

void EnemySpawner::Draw(sf::RenderWindow& window)
{
	for (Enemy& enemy : enemies)
	{
		enemy.Draw(window);
	}
}
