/**
* @file player.h
* @brief Player movement and health management functions header file
* @author Jack Duignan
* @date 2016-11-30
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t health;
    bool hasFired;    
} Player_t;

/** Intialise the player
 * @param x x position of the player
 * @param y y position of the player
 * @param startHealth health of the player
 * @return pointer to a Player_t struct
 */
Player_t* playerInit(uint8_t x, uint8_t y, uint8_t startHealth);

/** Check to see if the player needs to be moved
 * @param player pointer to a Player_t struct
 * 
 */
void playerUpdate(Player_t* player);

#endif