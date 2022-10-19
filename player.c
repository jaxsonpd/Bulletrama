/**
 * @file player.c
 * @author ben gunn (bgu37) jack duignan (jdu80)
 * @brief Player functionality declarations 
 * @date 2022-10-02
 */

#include "player.h"
#include "navswitch.h"
#include "game.h"

// Constants
#define UP NAVSWITCH_WEST
#define DOWN NAVSWITCH_EAST
#define LEFT NAVSWITCH_SOUTH
#define RIGHT NAVSWITCH_NORTH
#define FIRE NAVSWITCH_PUSH

// Global variables
static uint8_t moveSpeed, startHealth, maxMoveHeight; 

/**
 * @brief Set the player variables
 * 
 * @param moveSpeed the speed the player moves at
 * @param startHealth the health the player starts with
 * @param maxMoveHeight the maximum height the player can move to
 */
void player_config(uint8_t newMoveSpeed, uint8_t newStartHealth, uint8_t newMaxMoveHeight) 
{
    moveSpeed = newMoveSpeed;
    startHealth = newStartHealth;
    maxMoveHeight = newMaxMoveHeight;
}

/**
 * @brief Intialise the player
 * 
 * @param x x position of the player
 * @param y y position of the player
 *
 * @return Player_t struct
 */
Player_t player_init(uint8_t x, uint8_t y) 
{
    Player_t player = {
        .x = x,
        .y = y,
        .health = startHealth,
        .hasFired = false,
        .canFire = true
    };

    return player;
}

/**
 * @brief Check to see if the player needs to be moved
 * 
 * @param player pointer to a Player_t struct
 */
void player_update(Player_t* player) 
{
    // Check to see if the nav switch has moved
    if (navswitch_push_event_p(UP)) {
        // User is trying to move up
        if (player->y <= maxMoveHeight) {
            // Move the player up
            player->y += moveSpeed;
        } 
    } else if (navswitch_push_event_p(DOWN)) {
        // The user is trying to move down
        if (player->y > 0) {
            // Move the player down
            player->y -= moveSpeed;
        } 
    } else if (navswitch_push_event_p(LEFT)) {
        // The user is trying to move left
        if (player->x > 0) {
            // Move the player left
            player->x -= moveSpeed;
        } 
    } else if (navswitch_push_event_p(RIGHT)) {
        // The user is trying to move the right
        if (player->x < MAX_X) {
            // Move the player right
            player->x += moveSpeed;
        }
    } else if (navswitch_push_event_p(FIRE)) {
        // The user is trying to fire
        // Check to see if the player can fire
        if (player->canFire) {
            // The player can fire
            // Set the player to have fired
            player->hasFired = true;
            // Set the player to not be able to fire
            player->canFire = false;
        }
    }

}
