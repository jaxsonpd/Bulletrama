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

uint8_t level = 1;
bool gameOver = false;
bool won = true;
bool pause = false;

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

/** Run the game for Level 1
 * 
 */
void levelOne() {
    // Tell the other board that level 1 is being played

    // Initialise the game
    Player_t* player;
    int* gameBoard;
    uint8_t walls[MAX_Y][MAX_X] = {
        {0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    levelOneInit(player, gameBoard);

    // Start the game loop
    while (!gameOver) {
        // Update the player information
        playerUpdate(player);
                    
        // Update the enemy information (IR)

        // Check pause
        if (pause) {
            // Send message to other board to pause

            // Pause the game
            displayGamePause();

            pause = false;
        }

        // Update the bullet information

        // Check for collisions

        // Check for game over for itself
        if (player->health == 0) {
            gameOver = true;
            won = false;

            // Tell the other board that the game is over
        }

        // Check for game over for the other board

        // Update the screen
        displayGameBoard(player, bullets, walls, numBullets);

        // Repeat
    }
    // Display game over screen
    displayGameOver();

    if (!won) {
        // Display win screen
        displayGameDefeat();
    } else {
        // Display lose screen
        displayGameWin();
    }

    gameOver = false;
}

int main(void) {
    // Initialise the controller
    system_init();

    // Start the main loop
    while (1) {
        if (level == 1) {
            // Chose Level 1
            levelOne();
        }
    }


}

