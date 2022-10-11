/**
 * @file game.c
 * @brief The main excution file for the game
 * @author Jack Duignan and Ben Gunn.
 * @date 2022-10-03
 */

/**
 * Main flow of the game
 * 1. Initialise the game
 * 2. Start the game loop
 * 3. update the player information
 * 4. update the enemy information (IR)
 * 5. update the bullet information
 * 6. check for collisions
 * 7. check for game over
 * 6. update the screen
 * 7. repeat
 */

#include "player.h"
#include "game.h"
#include "system.h"
#include "gameDisplay.h"
#include "navswitch.h"
#include "bullet.h"
#include "pacer.h"
#include "levels.h"

#define PACER_FREQ 300

uint8_t level = 1;
bool gameOver = false;
bool won = true;
bool pause = false;

/** Destroy walls if bullets have hit them
 * @param walls an array of walls
 * @param bullets an array of bullets
 * @param numBullets the number of bullets
*/
void destroyWalls(uint8_t walls[MAX_Y + 1][MAX_X + 1], Bullet_t bullets[], uint8_t numBullets) {
    // Loop through Bullets checking walls
}

int main(void) {
    // Initialise the controller
    system_init();
    initGameBoard();
    pacer_init(PACER_FREQ);
    
    bulletConfig(L1_BULLET_SPEED);
    playerConfig(L1_MOVE_SPEED, L1_START_HEALTH, L1_MAX_HEIGHT);


    Player_t player = playerInit(0, 0);

    Bullet_t bullets[5] = {0};
    uint8_t numBullets = 0;
    
    uint16_t bulletDelay = 0;
    uint16_t bulletUpdateDelay = 0;

    uint8_t walls[MAX_Y + 1][MAX_X + 1] = {
        {0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    // Start the main loop
    while (!gameOver) {
        // Pacer Wait
        pacer_wait();

        //Nav update
        navswitch_update();
        
        // Player Position update
        playerUpdate(&player);

        // Get new IR info

        // Add new bullets from IR and player
        if (player.hasFired && player.canFire) {
            // Add new bullet at player postion

            // Reset player 
            player.hasFired = false;
            bulletDelay = 0;
        }

        if (!(player.canFire) && bulletDelay > L1_BULLET_FIRE_DELAY) {
            player.canFire = true;
        }

            // Add IR bullets

        // Update bullet postion if it is time to
        if (bulletUpdateDelay > L1_BULLET_UPDATE_WAIT) {
            // Update bullets
        }

        // Update walls if bullet has hit them
        destroyWalls(walls, bullets, numBullets);

        // Check for health and game over
            // Check to see if a enemy bullet is on player postion

            // Update player health if so

        if (player.health == 0) {
            gameOver = true;
            won = false;

            // tell there board they have won
        } 

        // Update the game board
        displayGameBoard(&player, bullets, walls, numBullets);

        // Update timers
        bulletDelay += !(player.canFire) ? 1 : 0;
        bulletUpdateDelay ++;
    }
}

