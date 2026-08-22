#include "Player.h"
#include <algorithm>

Player::Player() : playerSprite(playerIdleTexture), currentFrame(0), animationTimer(0.0f), frameDuration(0.1f)
{
	playerIdleTexture.loadFromFile("Images/Player_Idle.png");
	playerRunTexture.loadFromFile("Images/Player_Run.png");
	playerAttackTexture.loadFromFile("Images/Player_Attack.png");

	playerSprite.setTextureRect(sf::IntRect({ 0, 0 }, { playerFrameWidth, playerFrameHeight }));
	playerSprite.setOrigin({ playerFrameWidth / 2.0f, playerFrameHeight / 2.0f });
	playerSprite.setPosition({ 864.f, 444.f });

	attackHitbox.setRadius(attackRadius);
	attackHitbox.setOrigin({ attackRadius, attackRadius });
}

void Player::MovePlayer(sf::Vector2f direction, float deltaTime)
{
	float movement = moveSpeed * deltaTime;

	playerSprite.move(direction * movement);
}

bool Player::IsAttacking() const
{
	return isAttacking;
}

bool Player::IsAttackHitboxActive() const
{
	return isAttackHitboxActive;
}

sf::FloatRect Player::GetAttackBounds() const
{
	return attackHitbox.getGlobalBounds();
}

int Player::GetDamageToImpart() const
{
	return attackDamage;
}

void Player::TakeDamage(int damage)
{
	playerHealth -= damage;
}

bool Player::IsDead() const
{
	return playerHealth <= 0;
}

void Player::PerformAttack()
{
	if (isAttacking)
	{
		return; 
	}

	isAttacking = true;

	SetAnimation(Enums::AnimationStates::Attack);

	sf::Vector2f offset;

	if (currentFacingDirection == Enums::FacingDirection::Right)
	{
		offset = { 15.0f, 0.0f };
	}
	else
	{
		offset = { -15.0f, 0.0f };
	}

	attackHitbox.setPosition(playerSprite.getPosition() + offset);
}

sf::Vector2f Player::GetPosition()
{
	return playerSprite.getPosition();
}

void Player::ClampToWindow(const sf::Vector2u& windowSize)
{
	sf::Vector2f position = playerSprite.getPosition();

	float halfWidth = playerFrameWidth / 2.0f;
	float halfHeight = playerFrameHeight / 2.0f;

	position.x = std::clamp(position.x, halfWidth, windowSize.x - halfWidth);
	position.y = std::clamp(position.y, halfHeight, windowSize.y - halfHeight);

	playerSprite.setPosition(position);
}

void Player::SetFacingDirection(Enums::FacingDirection facingDirection)
{
	currentFacingDirection = facingDirection;

	if (currentFacingDirection == Enums::FacingDirection::Right)
	{
		playerSprite.setScale({ 1.0f, 1.0f });
	}
	else
	{
		playerSprite.setScale({ -1.0f, 1.0f });
	}
}

void Player::SetAnimation(Enums::AnimationStates state)
{
	if (currentAnimationState == state)
	{
		return;
	}

	currentAnimationState = state;

	currentFrame = 0;
	animationTimer = 0.0f;

	switch (currentAnimationState)
	{
	case Enums::AnimationStates::Idle:
		playerSprite.setTexture(playerIdleTexture);
		currentAnimationFrameCount = playerIdleFrameCount;
		break;
	case Enums::AnimationStates::Run:
		currentAnimationFrameCount = playerRunFrameCount;
		playerSprite.setTexture(playerRunTexture);
		break;
	case Enums::AnimationStates::Attack:
		currentAnimationFrameCount = playerAttackFrameCount;
		playerSprite.setTexture(playerAttackTexture);
		break;
	case Enums::AnimationStates::Death:
		break;
	default:
		break;
	}

	playerSprite.setTextureRect(sf::IntRect({ 0, 0 }, { playerFrameWidth, playerFrameHeight }));
}

void Player::AnimatePlayer(float deltaTime)
{
	animationTimer += deltaTime;

	if (animationTimer >= frameDuration)
	{
		animationTimer -= frameDuration;
		currentFrame++;

		if (currentAnimationState == Enums::AnimationStates::Attack)
		{
			isAttackHitboxActive = (currentFrame >= (playerAttackFrameCount / 2) && currentFrame < playerAttackFrameCount);
		}

		if (currentFrame >= currentAnimationFrameCount)
		{
			if (currentAnimationState == Enums::AnimationStates::Attack)
			{
				currentFrame = currentAnimationFrameCount - 1;

				isAttackHitboxActive = false;
				isAttacking = false;
			}
			else
			{
				currentFrame = 0;
			}
		}

		playerSprite.setTextureRect(sf::IntRect({ currentFrame * playerFrameWidth, 0 }, { playerFrameWidth, playerFrameHeight }));
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(playerSprite);
}
