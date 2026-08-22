#pragma once

#include <SFML/Graphics.hpp>
#include "EnumHolder.h"

class Enemy
{
private:
	sf::RectangleShape enemyShape;
	
	float collisionRadius = 30.0f;
	float moveSpeed = 100.0f;
	int health = 1;
	int damage = 1;
	float attackCooldown = 1.5f;
	float attackTimer = 0.0f;


public:
	Enums::EnemyTypes CurrentEnemyType;

	void Initialize(sf::Vector2f postion);
	void MoveTowardsPlayer(sf::Vector2f playerPosition, float deltaTime);

	void Update(float deltaTime);

	void AttackPlayer();
	bool IsDead() const;
	void TakeDamage(int damage);
	int GetDamageToImpart();
	float GetAttackCooldown();
	bool CanAttack() const;

	void MoveBy(sf::Vector2f offset);

	sf::Vector2f GetPosition() const;
	float GetCollisionRadius() const;

	sf::FloatRect GetBounds() const;
	void Draw(sf::RenderWindow& window);
};

