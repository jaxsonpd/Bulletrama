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
 * @param enemy val -1 is enemy
 */

void bulletConfig(uint8_t Speed) {
    bulletSpeed = Speed;
}

/**
 * @brief declare the origin and bullet direction
 * 
 * @param x 
 * @param y 
 * @param owner takes +1==friend  -1== enemy
 * @return Bullet_t 
 */

Bullet_t bulletInit(uint8_t x, int8_t y, uint8_t owner) 
{
    Bullet_t bullet ={
        .owner = owner,
        .speed = bulletSpeed,
        .x = x,
        .y = y
    };
    return bullet;
}

/** Update the location of the bullet
 * 
 * @param bullet an array of bullets
 */
void bulletUpdate(Bullet_t bullet[10])
{
    for (uint8_t i = 0; i < 10; i++)
    {
        if (bullet[i].y != 10) {
            bullet[i].y += bullet[i].owner;
        }
    }
}

/** Add a new bullet to the array if possible
 * 
 * @param bullets an array of bullets
 * @param numBullets the number of bullets in the array
 * @param bullet the bullet to add
 * 
 * @return true if bullet added
 */
bool bulletAdd(Bullet_t bullets[], uint8_t numBullets, Bullet_t bullet) {
    uint8_t i = 0;
    bool found_empty = false;

    while (i < numBullets && !found_empty) {
        if(bullets[i].y == 10) {
                bullets[i] = bullet;
                found_empty = true;
        }
        i ++;
    }

    return found_empty;
}


