#include "Enemy.h"

void Enemy::Initialize(sf::Vector2f postion)
{
	enemyShape.setSize({ 40.0f, 40.0f });
	enemyShape.setFillColor(sf::Color::Magenta);
	enemyShape.setOrigin({ 20.0f, 20.0f });
	enemyShape.setPosition(postion);
}

void Enemy::MoveTowardsPlayer(sf::Vector2f playerPosition, float playerCollisionRadius, float deltaTime)
{
	sf::Vector2 direction = playerPosition - enemyShape.getPosition();

	float distance = direction.length();
	float stopDistance = playerCollisionRadius + collisionRadius;

	if (distance > stopDistance)
	{
		direction /= distance;
		enemyShape.move(direction * moveSpeed * deltaTime);
	}
}

void Enemy::Update(float deltaTime)
{
	if (attackTimer < attackCooldown)
	{
		attackTimer += deltaTime;
	}
}

bool Enemy::CanAttack() const
{
	return attackTimer >= attackCooldown;
}

void Enemy::TakeDamage(int damage)
{
	health -= damage;
}

int Enemy::GetDamageToImpart()
{
	return damage;
}

bool Enemy::IsDead() const
{
	return health <= 0;
}

void Enemy::AttackPlayer()
{
	attackTimer = 0.0f;
}

void Enemy::MoveBy(sf::Vector2f offset)
{
	enemyShape.move(offset);
}

sf::Vector2f Enemy::GetPosition() const
{
	return enemyShape.getPosition();
}

float Enemy::GetCollisionRadius() const
{
	return collisionRadius;
}

sf::FloatRect Enemy::GetBounds() const
{
	return enemyShape.getGlobalBounds();
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemyShape);
}