/**
* @file player.h
* @brief Player movement and health management functions header file
* @author Jack Duignan (Jdu80), 
* @date 2020-11-30
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
    bool canFire; 
} Player_t;

// Constants
#define UP NAVSWITCH_WEST
#define DOWN NAVSWITCH_EAST
#define LEFT NAVSWITCH_SOUTH
#define RIGHT NAVSWITCH_NORTH
#define FIRE NAVSWITCH_PUSH

/** Set the player variables
 * @param moveSpeed the speed the player moves at
 * @param startHealth the health the player starts with
 * @param maxHeight the maximum height the player can move to
 */
void playerConfig(uint8_t moveSpeed, uint8_t startHealth, uint8_t maxHeight);

/** Intialise the player
 * @param x x position of the player
 * @param y y position of the player
 * @return Player_t struct
 */
Player_t playerInit(uint8_t x, uint8_t y);

/** Check to see if the player needs to be moved
 * @param player pointer to a Player_t struct
 */
void playerUpdate(Player_t* player);

#endif
