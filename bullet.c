/**
 * @file bullet.c
 * @author ben gunn (bgu37)
 * @brief bullet movement location and ownership
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "bullet.h"

#include "game.h"

// Global variables
uint8_t bulletSpeed, friend, enemy;

// ==================================================== Function Definitions ====================================================
/** Set the player variables
 * @param bulletSpeed the speed the bullet moves at
 * @param friend val 1 is my bullet
 * @param enemy val 0 is enemy
 */

void bulletConfig(uint8_t Speed) {
    bulletSpeed = Speed;
}

Bullet_t bulletInit(uint8_t x, uint8_t y, uint8_t owner) 
{
    Bullet_t bullet ={
        .owner = owner,
        .speed = bulletSpeed,
        .x = x,
        .y = y
    };
    return bullet;
}

void bulletUpdate(Bullet_t* bullet)
{
    if (bullet->owner == 1) {
        bullet->x += bulletSpeed;
    } else {
        bullet->x -= bulletSpeed;
    }
    
}
