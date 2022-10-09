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
uint8_t bulletSpeed, friend, enemy

// ==================================================== Function Definitions ====================================================
/** Set the player variables
 * @param bulletSpeed the speed the bullet moves at
 * @param friend val 1 is my bullet
 * @param enemy val 0 is enemy
 */
void bulletConfig(uint8_t bulletSpeed) {
    bulletSpeed = bulletSpeed;
}


}