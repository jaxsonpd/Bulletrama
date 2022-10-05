/**
 * @file player.c
 * @author Jack Duignan
 * @brief Player movement and health management functions
 * @date 2022-10-02
 */

#include "player.h"
#include "navswitch.h"
#include "game.h"

// Global variables
uint8_t moveSpeed, startHealth, maxMoveHeight; 

// ==================================================== Function Definitions ====================================================
/** Set the player variables
 * @param moveSpeed the speed the player moves at
 * @param startHealth the health the player starts with
 * @param maxMoveHeight the maximum height the player can move to
 */
void playerConfig(uint8_t moveSpeed, uint8_t startHealth, uint8_t maxMoveHeight) {
    moveSpeed = moveSpeed;
    startHealth = startHealth;
    maxMoveHeight = maxMoveHeight;
}

/** Intialise the player
 * @param x x position of the player
 * @param y y position of the player
 * @return Player_t struct
 */
Player_t playerInit(uint8_t x, uint8_t y) {
    Player_t player = {
        .x = x,
        .y = y,
        .health = startHealth,
        .hasFired = false,
        .canFire = true
    };

    return player;
}

/** Check to see if the player needs to be moved
 * @param player pointer to a Player_t struct
 */
void playerUpdate(Player_t* player) {
    // Update the navswitch
    navswitch_update();

    // Check to see if the nav switch has moved
    if (navswitch_push_event_p(UP)) {
        // User is trying to move up
        if (player->y < maxMoveHeight) {
            // Move the player up
            player->y += moveSpeed;
        } else {
            // Player is at the top of the screen
            // Do nothing
        }
    } else if (navswitch_push_event_p(DOWN)) {
        // The user is trying to move down
        if (player->y > 0) {
            // Move the player down
            player->y -= moveSpeed;
        } else {
            // Player is at the bottom of the screen
            // Do nothing
        }
    } else if (navswitch_push_event_p(LEFT)) {
        // The user is trying to move left
        if (player->x > 0) {
            // Move the player left
            player->x -= moveSpeed;
        } else {
            // Player is at the left of the screen
            // Do nothing
        }
    } else if (navswitch_push_event_p(RIGHT)) {
        // The user is trying to move the right
        if (player->x < MAX_X) {
            // Move the player right
            player->x += moveSpeed;
        } else {
            // Player is at the right of the screen
            // Do nothing
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
        } else {
            // The player cannot fire
            // Do nothing
        }
    }

}