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
#include "button.h"
#include "game.h"
#include "bullet.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "pacer.h"

// ==================================================== Function Definitions ====================================================
/** Initilise the game board 
 * 
 * @param pacerRate
 * @param messageRate
 */
void initGameBoard(uint16_t pacerRate, uint16_t messageRate) {
    // display_init();
    tinygl_init (pacerRate);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (messageRate);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    
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


/** Display Game Over
 * 
*/

void game_Over(void) {
    tinygl_text("GAME OVER");
    button_update();
    while (!button_push_event_p (0)) {
        pacer_wait();
        tinygl_update();
        button_update();
    }
}

void game_Win(void) {
    tinygl_text("YOU WIN!");
    button_update();
    while (!button_push_event_p (0)) {
        pacer_wait();
        button_update();
        tinygl_update();
    }
    
}

void game_Loss(void) {
    tinygl_text("YOU LOSER :(");
    button_update();
    while (!button_push_event_p (0)) {
        button_update();
        pacer_wait();
        tinygl_update();
    }
}

void display_Pause(void) {
    tinygl_text("PAUSED");
    button_update();
    while (!button_push_event_p (0)) {
        pacer_wait();
        button_update();
        tinygl_update();
    }
}