#pragma once

#include <SFML/Graphics.hpp>
#include "EnumHolder.h"

class InputHandler
{
public:
	sf::Vector2f GetMovementDirection();

	bool IsAttackPressed();

	Enums::FacingDirection GetFacingDirection();

	bool IsEnemyManualSpawnInput();

private:
	Enums::FacingDirection facingDirection = Enums::FacingDirection::Right;

	bool previousAttackState = false;

};

