/**
 * @file gameDisplay.h
 * @author ben gunn (bgu37) jack duignan (jdu80)
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

/**
 * @brief Display the game board
 * 
 * @param player a pointer to the player struct
 * @param bullets a pointer to an array of pointers to bullet structs 
 * @param walls a pointer to an array of walls
 * @param numBullets the length of the bullets array
 */
void display_game_board(Player_t* player, Bullet_t bullets[10], uint8_t walls[MAX_Y + 1][MAX_X+ 1], uint8_t numBullets);

/** @brief Initilise the game board 
 * 
 * @param pacerRate
 * @param messageRate
 */
void init_game_board(uint16_t pacerRate, uint16_t messageRate);

/** 
 * @brief Display the title screen
 * 
 */
void display_title_screen(void);

/** 
 * @brief Display Game Over
 * 
*/
void game_over(void);

/** 
 * @brief Display Game Win
 * 
 */
void game_win(void);

/**
 * @brief Display Game Loss
 * 
 */
void game_loss(void);

/** 
 * @brief Display the pause screen
 * 
 */
void display_pause(void);
#endif
