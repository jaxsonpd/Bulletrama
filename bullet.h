/**
 * @file bullet.h
 * @author ben gunn (bgu37) jack duignan (jdu80)
 * @brief header file for the bullet functionality
 * @date 2022-10-10
 * 
 */

#ifndef BULLET_H
#define BULLET_H

#include <stdbool.h>
#include <stdint.h>

// Bullet struct
typedef struct {
    uint8_t x;
    int8_t y;
    int8_t owner;
    uint8_t speed;
     
} Bullet_t;


/** Set the Bullet variables
 * @param BulletSpeed the speed the bullet moves at
 */
void bullet_config(uint8_t speed);

/** Intialise the bullet
 * @param x x position of the bullet
 * @param y y position of the bullet
 * @param owner direction of bullet and ownership 0 == enemy
 * 
 * @return Bullet_t struct
 */
Bullet_t bullet_init(uint8_t x, int8_t y, uint8_t owner);

/** Update the location of the bullet
 * @param bullet an array of bullets
 * 
 */
void bullet_update(Bullet_t bullet[]);

/** Add a new bullet to the array if possible
 * 
 * @param bullets an array of bullets
 * @param numBullets the number of bullets in the array
 * @param bullet the bullet to add
 * 
 * @return true if the bullet was added
 */
bool bullet_add(Bullet_t bullets[], uint8_t numBullets, Bullet_t bullet);
#endif
