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
void display_game_board(Player_t* player, Bullet_t bullets[10], uint8_t walls[MAX_Y + 1][MAX_X+ 1], uint8_t numBullets);

/** Initilise the game board 
 * 
 * @param pacerRate
 * @param messageRate
 */
void init_game_board(uint16_t pacerRate, uint16_t messageRate);

/** Get the level to be played Next
 * 
 * @return uint8_t 
 */
uint8_t get_level(void);

/** Display the title screen
 * 
 */
void display_title_screen(void);

/** Display Game Over
 * 
*/
void game_over(void);

/** Display Game Win
 * 
 */
void game_win(void);

/** Display Game Loss
 * 
 */
void game_loss(void);

/** Display the pause screen
 * 
 */
void display_pause(void);
#endif
