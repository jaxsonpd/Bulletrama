<<<<<<< HEAD
/**
 * @file bullet.h
 * @author ben gunn (bgu37)
 * @brief contains the structs for bullet position, speed and owner
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BULLET_H
#define BULLET_H

#include <stdbool.h>
#include <stdint.h>



typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t owner;
    uint8_t speed;
     
} Bullet_t;

/** Set the Bullet variables
 * @param BulletSpeed the speed the bullet moves at
 */
void bulletConfig(uint8_t speed);

/** Intialise the bullet
 * @param x x position of the bullet
 * @param y y position of the bullet
 * @param owner direction of bullet and ownership 0 == enemy
 * @return Bullet_t struct
 */
Bullet_t bulletInit(uint8_t x, uint8_t y, uint8_t owner);

/** Check to see if the player needs to be moved
 * @param player pointer to a Player_t struct
 */
void bulletUpdate(Bullet_t* bullet);

#endif
=======

>>>>>>> e922864636731ac02554f5026a8145d577ea135f
