#pragma once

#include <SFML/Graphics.hpp>

class ExpCollectable
{
public:
	void Initialize(sf::Vector2f position);
	bool IsInRange(sf::Vector2f playerPosition) const;
	void Collect();

	bool IsCollected() const;

	void Draw(sf::RenderWindow& window);

private:
	sf::CircleShape expShape;

	float collectRange = 30.0f;
	int expValue = 1;

	bool isCollected = false;
};

