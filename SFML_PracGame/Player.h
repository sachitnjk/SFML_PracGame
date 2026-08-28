#pragma once

#include <SFML/Graphics.hpp>
#include "EnumHolder.h"
#include <iostream>

class Player
{
public:
    Player();

    void MovePlayer(sf::Vector2f direction, float deltaTime);
    void SetFacingDirection(Enums::FacingDirection facingDirection);
    
    void PerformAttack();
    bool IsAttacking() const;
    bool IsAttackHitboxActive() const;
    sf::FloatRect GetAttackBounds() const;
    sf::FloatRect GetBounds() const;
    int GetDamageToImpart() const;

    void TakeDamage(int damage);
    bool IsDead() const;

    void SetAnimation(Enums::AnimationStates state);
    void AnimatePlayer(float deltaTime);
    
    sf::Vector2f GetPosition();

    void ClampToWindow(const sf::Vector2u& windowSize);
    
    void Draw(sf::RenderWindow& window);

private:
    sf::Texture playerIdleTexture;
    sf::Texture playerRunTexture;
    sf::Texture playerAttackTexture;
    sf::Texture playerHealthTexture;
    sf::Texture playerDeathTexture;

    sf::Sprite playerSprite;
    sf::Sprite healthSprite;

    sf::CircleShape attackHitbox;

    Enums::AnimationStates currentAnimationState = Enums::AnimationStates::Idle;
    Enums::FacingDirection currentFacingDirection = Enums::FacingDirection::Right;

    int  playerHealth = 3;
    float moveSpeed = 300.0f;

    float damageFlashTimer = 0.0f;
    float damageFlashDuration = 0.1f;

    int currentFrame = 0;
    float animationTimer = 0.0f;
    float frameDuration = 0.1f;

    int playerFrameWidth = 192;
    int playerFrameHeight = 192;

    int playerDeathFrameWidth = 64;
    int playerDeathFrameHeight = 64;

    int playerHealthWidth = 32;
    int playerHealthHeight = 32;

    int currentAnimationFrameCount;
    int playerIdleFrameCount = 8;
    int playerRunFrameCount = 6;
    int playerAttackFrameCount = 4;
    int playerDeathFrameCount = 10;

    bool isAttacking = false;
    bool isAttackHitboxActive = false;
    float attackRadius = 65.0f;
    int attackDamage = 1;

};

