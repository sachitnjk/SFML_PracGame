#include "Player.h"
#include <algorithm>

Player::Player() : playerSprite(playerIdleTexture), healthSprite(playerHealthTexture), currentFrame(0), animationTimer(0.0f), frameDuration(0.1f)
{
	playerIdleTexture.loadFromFile("Images/Player_Idle.png");
	playerRunTexture.loadFromFile("Images/Player_Run.png");
	playerAttackTexture.loadFromFile("Images/Player_Attack.png");
	playerHealthTexture.loadFromFile("Images/Heart_Red.png");
	playerDeathTexture.loadFromFile("Images/Dust_Big.png");

	playerSprite.setTextureRect(sf::IntRect({ 0, 0 }, { playerFrameWidth, playerFrameHeight }));
	playerSprite.setOrigin({ playerFrameWidth / 2.0f, playerFrameHeight / 2.0f });
	playerSprite.setPosition({ 864.f, 444.f });

	healthSprite.setTextureRect(sf::IntRect({ 0, 0 }, { playerHealthWidth, playerHealthHeight }));
	healthSprite.setScale({ 8.0f, 8.0f });

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

sf::FloatRect Player::GetBounds() const
{
	return playerSprite.getGlobalBounds();
}

int Player::GetDamageToImpart() const
{
	return attackDamage;
}

void Player::TakeDamage(int damage)
{
	playerHealth -= damage;

	playerSprite.setColor(sf::Color::Red);
	damageFlashTimer = damageFlashDuration;

	if (playerHealth <= 0)
	{
		SetAnimation(Enums::AnimationStates::Death);
	}
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

	int currentFrameWidth = playerFrameWidth;
	int currentFrameHeight = playerFrameHeight;

	playerSprite.setOrigin({playerFrameWidth / 2.0f, playerFrameHeight / 2.0f });

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
		currentAnimationFrameCount = playerDeathFrameCount;

		currentFrameWidth = playerDeathFrameWidth;
		currentFrameHeight = playerDeathFrameHeight;

		playerSprite.setTexture(playerDeathTexture);
		playerSprite.setOrigin({ currentFrameWidth / 2.0f, currentFrameHeight / 2.0f });
		break;
	default:
		break;
	}

	playerSprite.setTextureRect(sf::IntRect({ 0, 0 }, { currentFrameWidth, currentFrameHeight }));
}

void Player::AnimatePlayer(float deltaTime)
{
	animationTimer += deltaTime;

	//---Damage flash
	if (damageFlashTimer > 0.0f)
	{
		damageFlashTimer -= deltaTime;

		if (damageFlashTimer <= 0.0f)
		{
			damageFlashTimer = 0.0f;
			playerSprite.setColor(sf::Color::White);
		}
	}

	if (animationTimer >= frameDuration)
	{
		animationTimer -= frameDuration;
		currentFrame++;

		int frameWidth = playerFrameWidth;
		int frameHeight = playerFrameHeight;

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
			else if (currentAnimationState == Enums::AnimationStates::Death)
			{
				currentFrame = currentAnimationFrameCount - 1;
			}
			else
			{
				currentFrame = 0;
			}
		}

		if (currentAnimationState == Enums::AnimationStates::Death)
		{
			frameWidth = playerDeathFrameWidth;
			frameHeight = playerDeathFrameHeight;
		}

		playerSprite.setTextureRect(sf::IntRect({ currentFrame * frameWidth, 0 }, { frameWidth, frameHeight }));
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(playerSprite);

	for (int i = 0; i < playerHealth; i++)
	{
		healthSprite.setPosition({ 20.0f + i * 20.0f, 20.0f });

		window.draw(healthSprite);
	}
}
