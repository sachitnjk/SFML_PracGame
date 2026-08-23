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

void EnemySpawner::Update(sf::Vector2f playerPosition, const sf::Vector2u& windowSize, float deltaTime)
{
	for (Enemy& enemy : enemies)
	{
		enemy.MoveTowardsPlayer(playerPosition, deltaTime);
		enemy.Update(deltaTime);
	}

	//---Auto spawn 
	spawnTimer += deltaTime;
	if (spawnTimer >= spawnInterval && enemies.size() < maxEnemySpawn)
	{
		SpawnEnemy(windowSize);

		spawnTimer = 0.0f;
	}

	//---Enem dista nce maintain
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = i + 1; j < enemies.size(); j++)
		{
			sf::Vector2f direction = enemies[i].GetPosition() - enemies[j].GetPosition();

			float distance = direction.length();
			float minimumDistance = enemies[i].GetCollisionRadius() + enemies[j].GetCollisionRadius();

			if (distance < minimumDistance && distance > 0.0f)
			{
				direction /= distance;

				float overlap = minimumDistance - distance;

				enemies[i].MoveBy(direction * (overlap * 0.5f));
				enemies[j].MoveBy(-direction * (overlap * 0.5f));
			}
		}
	}
}

void EnemySpawner::CheckPlayerAttack(const Player& player)
{
	if (!player.IsAttackHitboxActive())
	{
		return;
	}

	sf::FloatRect attackBounds = player.GetAttackBounds();

	for (auto it = enemies.begin(); it != enemies.end();)
	{
		if (attackBounds.findIntersection(it->GetBounds()))
		{
			it->TakeDamage(player.GetDamageToImpart());

			if (it->IsDead())
			{
				it = enemies.erase(it);
				continue;
			}
		}

		++it;
	}
}

void EnemySpawner::CheckEnemyToPlayerCollision(Player& player)
{
	sf::FloatRect playerBounds = player.GetBounds();

	//---Collision area shrink
	playerBounds.position += { 64.0f, 64.0f };
	playerBounds.size -= { 128.0f, 128.0f };

	for (Enemy& enemy : enemies)
	{
		if (enemy.GetBounds().findIntersection(playerBounds) && enemy.CanAttack())
		{
			enemy.AttackPlayer();
			player.TakeDamage(enemy.GetDamageToImpart());
			break;
		}
	}
}

void EnemySpawner::Draw(sf::RenderWindow& window)
{
	for (Enemy& enemy : enemies)
	{
		enemy.Draw(window);
	}
}
