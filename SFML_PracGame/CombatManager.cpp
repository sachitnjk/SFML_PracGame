#include "CombatManager.h"

CombatManager::CombatManager(EnemySpawner& enemySpawner) : enemySpawnerRef(enemySpawner)
{
}

void CombatManager::CheckPlayerAttack(const Player& player)
{
	if (!player.IsAttackHitboxActive())
	{
		return;
	}

	sf::FloatRect attackBounds = player.GetAttackBounds();

	for (auto it = GetSpawnedEnemies().begin(); it != GetSpawnedEnemies().end();)
	{
		if (attackBounds.findIntersection(it->GetBounds()))
		{
			it->TakeDamage(player.GetDamageToImpart());

			if (it->IsDead())
			{
				it = GetSpawnedEnemies().erase(it);
				continue;
			}
		}

		++it;
	}
}

void CombatManager::CheckEnemyToPlayerCollision(Player& player)
{
	sf::FloatRect playerBounds = player.GetBounds();

	//---Collision area shrink
	playerBounds.position += { 64.0f, 64.0f };
	playerBounds.size -= { 128.0f, 128.0f };

	for (Enemy& enemy : GetSpawnedEnemies())
	{
		if (enemy.GetBounds().findIntersection(playerBounds) && enemy.CanAttack())
		{
			enemy.AttackPlayer();
			player.TakeDamage(enemy.GetDamageToImpart());
			break;
		}
	}
}

std::vector<Enemy>& CombatManager::GetSpawnedEnemies()
{
	return enemySpawnerRef.GetSpawnedEnemiesRef();
}
