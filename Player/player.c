/**
 * @file player.c
 * @author Jack Duignan
 * @brief Player movement and health management functions
 * @date 2022-10-02
 */

#include "player.h"
#include "navswitch.h"

// Constants
#define MAX_HORIZONTAL 7
#define UP NAVSWITCH_WEST
#define DOWN NAVSWITCH_EAST
#define LEFT NAVSWITCH_SOUTH
#define RIGHT NAVSWITCH_NORTH
#define FIRE NAVSWITCH_PUSH

// Global variables
uint8_t moveSpeed, startHealth, maxHeight; 

// ==================================================== Function Definitions ====================================================
/** Set the player variables
 * @param moveSpeed the speed the player moves at
 * @param startHealth the health the player starts with
 * @param maxHeight the maximum height the player can move to
 */
void playerConfig(uint8_t moveSpeed, uint8_t startHealth, uint8_t maxHeight) {
    moveSpeed = moveSpeed;
    startHealth = startHealth;
    maxHeight = maxHeight;
}

/** Intialise the player
 * @param x x position of the player
 * @param y y position of the player
 * @return pointer to a Player_t struct
 */
Player_t* playerInit(uint8_t x, uint8_t y) {
    Player_t* player = malloc(sizeof(Player_t));
    player->x = x;
    player->y = y;
    player->health = startHealth;
    player->hasFired = false;
    player->canFire = true;

    return player;
}

/** Check to see if the player needs to be moved
 * @param player pointer to a Player_t struct
 */
void playerUpdate(Player_t* player) {
    // Intialise the navswitch (Not needed as done in navswitch_update())
    // navswitch_init(); 

    // Update the navswitch
    navswitch_update();

    // Check to see if the nav switch has moved
    if (navswitch_push_event_p(UP)) {
        // User is trying to move up
        if (player->y < maxHeight) {
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
        if (player->x < MAX_HORIZONTAL) {
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