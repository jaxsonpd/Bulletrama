/**
 * @file gameDisplay.h
 * @author Jack Duignan (Jdu80)
 * @brief Header file for the functions that display the game board
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include "player.h"
#include "game.h"
#include "bullet.h"

/** Display the game board
 * @param player a pointer to the player struct
 * @param bullets a pointer to an array of pointers to bullet structs 
 * @param walls a pointer to an array of walls
 * @param numBullets the length of the bullets array
 */
void displayGameBoard(Player_t* player, Bullet_t bullets[], uint8_t walls[MAX_Y + 1][MAX_X + 1], uint8_t numBullets);

/** Initilise the game board
 * 
 */
void initGameBoard(void);

#endif
