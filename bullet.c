/**
 * @file bullet.c
 * @author ben gunn (bgu37) jack duignan (jdu80)
 * @brief bullet initialisation movement location and ownership
 * @date 2022-10-10
 * 
 */

#include "bullet.h"
#include "game.h"

// Global variables
static uint8_t bulletSpeed;

/**
 * @brief Set the bullet configuration variables
 * 
 * @param bulletSpeed the speed the bullet moves at
 */
void bullet_config(uint8_t Speed) 
{
    bulletSpeed = Speed;
}

/**
 * @brief A bullet is had been fired. Declare the origin and bullet direction
 * 
 * @param x 
 * @param y 
 * @param owner takes +1==friend  -1== enemy
 * @return Bullet_t 
 */
Bullet_t bullet_init(uint8_t x, int8_t y, uint8_t owner) 
{
    Bullet_t bullet ={
        .owner = owner,
        .speed = bulletSpeed,
        .x = x,
        .y = y
    };
    return bullet;
}

/** 
 * @brief Update the location of the bullet by advancing in y direction. direction depends on ownership
 * 
 * @param bullet an array of bullets of bullet_t type
 */
void bullet_update(Bullet_t bullet[10])
{
    for (uint8_t i = 0; i < 10; i++) {
        if (bullet[i].y != 10) { // If not deleted
            bullet[i].y += bullet[i].owner;
        }
    }
}

/**
 * @brief Add a new bullet to the array if possible
 * 
 * @param bullets an array of bullets
 * @param numBullets the number of bullets in the array
 * @param bullet the bullet to add
 * s
 * @return true if bullet added
 */
bool bullet_add(Bullet_t bullets[], uint8_t numBullets, Bullet_t bullet) {
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


