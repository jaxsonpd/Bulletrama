/**
 * @file gameDisplay.c
 * @author ben gunn (bgu37) jack duignan (jdu80)
 * @brief Functions for displaying the game board
 * @date 2022-10-06
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

/**
 * @brief Initilise the game board 
 * 
 * @param pacerRate
 * @param messageRate
 */
void init_game_board(uint16_t pacerRate, uint16_t messageRate) 
{
    // display_init();
    tinygl_init (pacerRate);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (messageRate);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    
}

/**
 * @brief Display the walls of the game board
 *
 * @param walls pointer to a 2D array of walls
 */
static void display_walls(uint8_t walls[MAX_Y + 1][MAX_X + 1]) 
{
    // Display the walls
    for (uint8_t i = 0; i < MAX_Y; i++) {
        for (uint8_t j = 0; j <= MAX_X; j++) {
            if (walls[i][j] == 1) {
                display_pixel_set(i, 6 - j, 1);
            }
        }
    }
}

/**
 * @brief Display the game board
 * 
 * @param player a pointer to the player struct
 * @param bullets a pointer to an array of pointers to bullet structs 
 * @param walls a pointer to an array of walls
 * @param numBullets the length of the bullets array
 */
void display_game_board(Player_t* player, Bullet_t bullets[10], uint8_t walls[MAX_Y + 1][MAX_X+ 1], uint8_t numBullets) 
{
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
    display_walls(walls);

    // Update the display
    display_update();
}

/**
 * @brief Display the title screen
 * 
*/
void display_title_screen(void) 
{
    tinygl_text("Bulletrama!");
    button_update();

    while (!button_push_event_p (0)) { // Display until the button is pressed
        pacer_wait();
        tinygl_update();
        button_update();
    }
}
/**
 * @brief Display Game Over
 * 
*/
void game_over(void) 
{
    tinygl_text("GAME OVER");
    button_update();
    while (!button_push_event_p (0)) { // Display until the button is pressed
        pacer_wait();
        tinygl_update();
        button_update();
    }
}

/**
 * @brief Display Game Win
 * 
 */
void game_win(void) 
{
    tinygl_text("YOU WIN!");
    button_update();
    while (!button_push_event_p (0)) { // Display until the button is pressed
        pacer_wait();
        button_update();
        tinygl_update();
    }
    
}

/**
 * @brief Display Game Loss
 * 
 */
void game_loss(void) 
{
    tinygl_text("YOU LOSER :(");
    button_update();
    while (!button_push_event_p (0)) { // Display until the button is pressed
        button_update();
        pacer_wait();
        tinygl_update();
    }
}

/** 
 * @brief Display the pause screen
 * 
 */
void display_pause(void) 
{
    tinygl_text("PAUSED");
    button_update();
    while (!button_push_event_p (0)) { // Display until the button is pressed
        pacer_wait();
        button_update();
        tinygl_update();
    }
}
