#include <SFML/Graphics.hpp>
#include "Player.h"
#include "InputHandler.h"
#include "EnemySpawner.h"
#include "EnemyManager.h"
#include "CombatManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML Survivor");
    Player player;
    InputHandler inputHandler;
    EnemySpawner enemySpawner;
    EnemyManager enemyManager(enemySpawner);
    CombatManager combatManager(enemySpawner);
    sf::Clock clock;


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        //---Movement
        if (!player.IsAttacking() && !player.IsDead())
        {
            sf::Vector2f movementDirection = inputHandler.GetMovementDirection();
            player.SetFacingDirection(inputHandler.GetFacingDirection());
            if (movementDirection != sf::Vector2{ 0.0f, 0.0f })
            {
                movementDirection = movementDirection.normalized();

                player.MovePlayer(movementDirection, deltaTime);
                player.SetAnimation(Enums::AnimationStates::Run);
            }
            else
            {
                player.SetAnimation(Enums::AnimationStates::Idle);
            }
        }

        //---Attack
        if (inputHandler.IsAttackPressed() && !player.IsDead())
        {
            player.PerformAttack();
        }

        enemySpawner.Update(window.getSize(), deltaTime);

        if (!player.IsDead())
        {
            enemyManager.Update(player.GetPosition(), player.GetCollisionRadius(), deltaTime);
            combatManager.CheckPlayerAttack(player);
            combatManager.CheckEnemyToPlayerCollision(player);
        }

        player.ClampToWindow(window.getSize());
        player.AnimatePlayer(deltaTime);

        window.clear();

        enemySpawner.Draw(window);
        player.Draw(window);
        
        window.display();
    }
}