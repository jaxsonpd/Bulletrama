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

uint8_t level = 1;
bool gameOver = false;
bool won = true;
bool pause = false;

int main(void) {
    // Initialise the controller
    system_init();
    initGameBoard();
    playerConfig(L1_MOVE_SPEED, L1_START_HEALTH, L1_MAX_HEIGHT);

    Player_t player = playerInit(0, 0);

    int* bullets[1] = {0};
    int numBullets = 0;
    
    uint8_t walls[MAX_Y][MAX_X] = {
        {0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    // Start the main loop
    while (1) {
        
        navswitch_update();

        playerUpdate(&player);
        
        displayGameBoard(&player, bullets, walls, numBullets);
    }


}

