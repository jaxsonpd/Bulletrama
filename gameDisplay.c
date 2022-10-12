/**
 * @file gameDisplay.c
 * @author Jack Duignan
 * @brief Functions for displaying the game board
 * @version 0.1
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "gameDisplay.h"
#include "display.h"
#include "game.h"
#include "bullet.h"

// ==================================================== Function Definitions ====================================================
/** Initilise the game board 
 */
void initGameBoard(void) {
    display_init();
}

/** Display the walls of the game board
 * @param walls pointer to a 2D array of walls
 */
static void displayWalls(uint8_t walls[MAX_Y + 1][MAX_X + 1]) {
    // Display the walls
    for (uint8_t i = 0; i < MAX_Y; i++) {
        for (uint8_t j = 0; j <= MAX_X; j++) {
            if (walls[i][j] == 1) {
                display_pixel_set(i, 6 - j, 1);
            }
        }
    }
}

/** Display the game board
 * @param player a pointer to the player struct
 * @param bullets a pointer to an array of pointers to bullet structs 
 * @param walls a pointer to an array of walls
 * @param numBullets the length of the bullets array
 */
void displayGameBoard(Player_t* player, Bullet_t bullets[10], uint8_t walls[MAX_Y + 1][MAX_X+ 1], uint8_t numBullets) {
    // Clear the display
    display_clear();

    // Display the player
    display_pixel_set(4 - player->y, 6 - player->x, 1);

    // Display the bullets`
    for (uint8_t i = 0; i < numBullets; i++) {
        if (bullets[i].y != 10) {
            display_pixel_set(4 - bullets[i].y, 6 - bullets[i].x, 1);
        }
    }

    // Display the Walls
    displayWalls(walls);

    // Update the display
    display_update();
}
