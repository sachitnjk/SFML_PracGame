#include "InputHandler.h"


sf::Vector2f InputHandler::GetMovementDirection()
{
    sf::Vector2f movementDirection{ 0.0f, 0.0f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        movementDirection.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        movementDirection.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        movementDirection.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        movementDirection.x += 1.0f;
    }

    if (movementDirection != sf::Vector2{ 0.0f, 0.0f })
    {
        movementDirection = movementDirection.normalized();
    }

    return movementDirection;
}

bool InputHandler::IsAttackPressed()
{
    bool currentAttackState = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    bool isAttackPressed = currentAttackState && !previousAttackState;
    previousAttackState = currentAttackState;

    return isAttackPressed;
}

Enums::FacingDirection InputHandler::GetFacingDirection()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        facingDirection = Enums::FacingDirection::Left;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        facingDirection = Enums::FacingDirection::Right;
    }

    return facingDirection;
}

bool InputHandler::IsEnemyManualSpawnInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        return true;
    }

    return false;
}
