#pragma once

#include <vector>
#include "Player.h"
#include "EnemySpawner.h"

class CombatManager
{
public:
	CombatManager(EnemySpawner& enemySpawner);

	void CheckPlayerAttack(const Player& player);
	void CheckEnemyToPlayerCollision(Player& player);

private:
	EnemySpawner& enemySpawnerRef;

	std::vector<Enemy>& GetSpawnedEnemies();
};

