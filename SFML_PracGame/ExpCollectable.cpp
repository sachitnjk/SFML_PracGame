#include "ExpCollectable.h"

void ExpCollectable::Initialize(sf::Vector2f position)
{
	expShape.setRadius(8.0f);
	expShape.setOrigin({ 8.0f, 8.0f });
	expShape.setFillColor(sf::Color::Yellow);
	expShape.setPosition(position);
}

bool ExpCollectable::IsInRange(sf::Vector2f playerPosition) const
{
	sf::Vector2f direction = playerPosition - expShape.getPosition();
	return direction.length() <= collectRange;
}

void ExpCollectable::Collect()
{
	isCollected = true;
}

bool ExpCollectable::IsCollected() const
{
	return isCollected;
}

void ExpCollectable::Draw(sf::RenderWindow& window)
{
	window.draw(expShape);
}
