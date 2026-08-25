#include "EnemyManager.h"

EnemyManager::EnemyManager(EnemySpawner& enemySpawner): enemySpawnerRef(enemySpawner)
{ }

void EnemyManager::Update(sf::Vector2f playerPosition, float deltaTime)
{
	std::vector<Enemy>& spawnedEnemiesRef = enemySpawnerRef.GetSpawnedEnemiesRef();

	//---Constant move towards player
	for(Enemy& enemy : spawnedEnemiesRef)
	{
		enemy.MoveTowardsPlayer(playerPosition, deltaTime);
		enemy.Update(deltaTime);
	}

	//---Enemy maintain distance between each other
	for (int i = 0; i < spawnedEnemiesRef.size(); i++)
	{
		for (int j = i + 1; j < spawnedEnemiesRef.size(); j++)
		{
			sf::Vector2f direction = spawnedEnemiesRef[i].GetPosition() - spawnedEnemiesRef[j].GetPosition();

			float distance = direction.length();
			float minimumDistance = spawnedEnemiesRef[i].GetCollisionRadius() + spawnedEnemiesRef[j].GetCollisionRadius();

			if (distance < minimumDistance && distance > 0.0f)
			{
				direction /= distance;

				float overlap = minimumDistance - distance;

				spawnedEnemiesRef[i].MoveBy(direction * (overlap * 0.5f));
				spawnedEnemiesRef[j].MoveBy(-direction * (overlap * 0.5f));
			}
		}
	}
}
