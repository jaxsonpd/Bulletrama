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

// ==================================================== Function Definitions ====================================================
/** Initilise the game board 
 */
void initGameBoard(void) {
    display_init();
}

/** Display the walls of the game board
 * @param walls pointer to a 2D array of walls
 */
static void displayWalls(uint8_t walls[MAX_X][MAX_Y]) {
    // Display the walls
    for (uint8_t i = 0; i < MAX_Y; i++) {
        for (uint8_t j = 0; j < MAX_X; j++) {
            if (walls[i][j] == 1) {
                display_pixel_set(i, j, 1);
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
void displayGameBoard(Player_t* player, int* bullets[], uint8_t walls[MAX_Y][MAX_X], uint8_t numBullets) {
    // Clear the display
    display_clear();

    // Display the player
    display_pixel_set(player->y, player->x, 1);

    // Display the bullets`
    for (uint8_t i = 0; i < numBullets; i++) {
        // display_pixel_set(bullets[i]->y, bullets[i]->x, 1);
    }

    // Display the Walls
    displayWalls(walls);

    // Update the display
    display_update();


}
