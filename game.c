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
    
    uint8_t walls[MAX_Y + 1][MAX_X + 1] = {
        {0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    // Start the main loop
    while (1) {
        // Pacer Wait
        pacer_wait();

        //Nav update
        navswitch_update();
        
        // Player Position update
        playerUpdate(&player);

        // Get new IR info

        // Add new bullets from IR and player

        // Update bullet postion if it is time to

        // Update walls if bullet has hit them

        // Check for health and game over

        // Update the game board
        displayGameBoard(&player, bullets, walls, numBullets);
    }


}

