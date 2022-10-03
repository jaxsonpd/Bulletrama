/**
 * @file game.c
 * @brief The main excution file for the game
 * @author Jack Duignan 
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

// Constants
#define L1_MOVE_SPEED 1
#define L1_START_HEALTH 3
#define L1_MAX_HEIGHT 2


uint8_t level = 1;
bool gameOver = false;

/** Initialise the game for Level 1
 * @param player pointer to a empty Player_t struct
 * @param gameBoard pointer to a empty GameBoard_t struct
 */
void levelOneInit(Player_t* player, int* gameBoard) {
    // Set the player variables
    playerConfig(L1_MOVE_SPEED, L1_START_HEALTH, L1_MAX_HEIGHT);

    // Initialise the player
    *player = playerInit(0, 0);

    // Initialise the game board
}

int main(void) {
    // Initialise the controller

    // Start the main loop
    while (1) {
        if (level == 1) {
            // Choosen Level 1
            // Tell the other board that level 1 is being played

            // Initialise the game
            Player_t* player;
            int* gameBoard;

            levelOneInit(player, gameBoard);

            // Start the game loop
            while (!gameOver) {
                // Update the player information
                playerUpdate(player);
                
                // Update the enemy information (IR)

                // Update the bullet information

                // Check for collisions

                // Check for game over

                // Update the screen

                // Repeat
            }
        }
    }


}

